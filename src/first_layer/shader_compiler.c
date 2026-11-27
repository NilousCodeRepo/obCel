#define _DEFAULT_SOURCE //needed for DT_xxx macros in C > C99
#include "../includes/base.h"
#include "../includes/internals.h"

u32 vertex_compile(const char*);
u32 fragment_compile(const char*);
u32 choose_f_type(const char*);
u32 shader_compile(char**);

char** buff_accumulate(const char*);

const char *get_filename_ext(const char*);
char* file_reader(char*);

void vertex_data(void);

#define BUFF_SIZE 1024*4
#define SHADER_COUNT 256

//provvisory count

static u16 TEXT_SIZE = 0;
static i8 COUNT = 0;

u32 shader_compile(char** buff)
{
    u32 prog_ID = glCreateProgram();

    //here count is as big as the number of shaders
    //isn't a bug since i am increasing the number of possible elements in an array at runtime?
    //it's a Variable Lenght Array, works since C99, but i don't like it
    u32 shaders[SHADER_COUNT];

    for(i8 i = 0; i < COUNT; ++i)
    {
        shaders[i] = choose_f_type(buff[i]);
        glAttachShader(prog_ID, shaders[i]);
    }
    glLinkProgram(prog_ID);

    i32 success; char info_log[LOG_SIZE] = {0};
    glGetProgramiv(prog_ID, GL_LINK_STATUS, &success);
    if(success == GL_FALSE) 
    {
        glGetProgramInfoLog(prog_ID, sizeof(info_log), NULL, info_log);
        printf(BASH_RED("ERROR")": Could NOT LINK shader [INFO LOG]:%s\n", info_log);
    }
    else
    {
        printf(BASH_GREEN("SUCCESS")": LINKING phase completed:%s\n", info_log);
    }

    //free the object associated with the ID that is that specific shader's ID
    for(u8 i = 0; i < COUNT; i++) glDeleteShader(shaders[i]);

    return(prog_ID);
}

u32 choose_f_type(const char* buff)
{
    u32 id = 0;
    char type[5] = {0};//needed 5 to avoid stupid *** stack smasking detected **
    for(u8 i = 0; i < 4; ++i) type[i] = buff[i];

    if(strcmp(type, "//VS") == 0) id = vertex_compile(buff);

    if(strcmp(type, "//FS") == 0) id = fragment_compile(buff); 
    return(id);
}

u32 vertex_compile(const char* vertex_file)
{
    u32 vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_file, NULL);
    glCompileShader(vertex_shader);
    
    i32 success; char info_log[LOG_SIZE] = {0};
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if(success == GL_FALSE) 
    {
        glGetShaderInfoLog(vertex_shader, LOG_SIZE, NULL, info_log);
        printf(BASH_RED("ERROR")": Could NOT COMPILE vertex shader [INFO LOG]:%s\n", info_log);
    }
    else
    {
        printf(BASH_GREEN("SUCCESS")": VERTEX shader compiled:%s\n", info_log);
    }

    return(vertex_shader);
}

u32 fragment_compile(const char* fragment_file)
{
    u32 fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_file, NULL);
    glCompileShader(fragment_shader);

    i32 success; char info_log[LOG_SIZE] = {0};
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if(success == GL_FALSE) 
    {
        glGetShaderInfoLog(fragment_shader, LOG_SIZE, NULL, info_log);
        printf(BASH_RED("ERROR")": Could NOT COMPILE fragment shader [INFO LOG]:%s\n", info_log);
    }
    else
    {
        printf(BASH_GREEN("SUCCESS")": FRAGMENT shader compiled:%s\n", info_log);
    }

    return(fragment_shader);
}

void vertex_data(void)
{
    const f32 VERTX_DATA[] = {
        // positions        
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        0.0f,  0.5f, 0.0f,  // top 
    };

    u32 VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VERTX_DATA), VERTX_DATA, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), (void*)(3 * sizeof(f32)));
    //glEnableVertexAttribArray(1);
}

const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

char* file_reader(char* file)
{
    FILE* f = fopen(file, "r");
    if(f == NULL) printf(BASH_RED("ERROR")": Could NOT OPEN shader file at \n");

    //check how many bytes is the file, by moving a "cursor"(file position indicator) then
    //reset the "cursor" position in the file
    fseek(f, 0, SEEK_END); 
    TEXT_SIZE = ftell(f); 
    fseek(f, 0, SEEK_SET);

    char* buffer = (char*) malloc(TEXT_SIZE + 1);
    if(buffer == NULL)printf(BASH_RED("ERROR")": ALLOCATION of buffer for shader compilation failed\n");
    // read into buffer one item the size of the file from the file
    fread(buffer, 1 , TEXT_SIZE, f);
    buffer[TEXT_SIZE] = '\0';
    fclose(f);
    
    return(buffer);
}

char** buff_accumulate(const char* path)
{
    DIR* dir;
    struct dirent* entry;
    char** buff = (char**)malloc(BUFF_SIZE);
    
    if((dir = opendir(path)) == NULL)
    {
        printf(BASH_RED("ERROR")": Could not open folder\n");
        //return(1);
    }

    char p[BUFF_SIZE];
    char ext[8];

    //TODO(nilou): the loop kind of works, but in the man of dirent is a "maybe" the fact that it
    //             can read the subsequen file(that after fs for example) try to use a simpler method 
    //             this loop is making me mad...
    while((entry = readdir(dir)) != NULL)
    {
        //serve a saltare l'attuale cartella, sennò ricorsione infinita ed errore
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        //sto creando la stringa che equivale al path
        snprintf(p, sizeof(p), "%s/%s", path, entry->d_name);
        
        //TODO(nilou): use debugger here
        //if(entry->d_type == DT_DIR)
        {
            snprintf(ext, sizeof(ext), "%s", get_filename_ext(entry->d_name));

            if(strcmp(ext, "fs") == 0)
            {
                buff[COUNT] = file_reader(p);
                COUNT++;
            }
            if(strcmp(ext, "vs") == 0)
            {
                buff[COUNT] = file_reader(p);
                COUNT++;
            }
        }
        // COMPUTA... COMPUTA MAKE THE SHADERS...COMPUTA!!
        // bugs = no; shaders = yes; efficiency = max(); 
    }

    closedir(dir);
    return(buff);
}
