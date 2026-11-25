#define _DEFAULT_SOURCE //needed for DT_xxx macros in C > C99
#include "../includes/base.h"
#include "../includes/internals.h"

u32 vertex_compile(const char*);
u32 fragment_compile(const char*);
u32 shader_compile(const char*);

const char *get_filename_ext(const char*);
char* file_reader(char*);

void vertex_data(void);

#define BUFF_SIZE 1024*4

static u16 TEXT_SIZE = 0;

u32 shader_compile(const char* path)
{
    DIR* dir;
    struct dirent* entry;
    char** buff = (char**)malloc(BUFF_SIZE);
    
    if((dir = opendir(path)) == NULL)
    {
        printf(BASH_RED("ERROR")": Could not open folder\n");
        return(1);
    }

    char p[BUFF_SIZE];
    char ext[8];
    u8 count = 0;

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
        printf("PATH: %s\n", path);
        
        //TODO(nilou): use debugger here
        if(entry->d_type == DT_DIR) shader_compile(p);

        snprintf(ext, sizeof(ext), "%s", get_filename_ext(entry->d_name));
        printf("EXT: %s\n", ext);

        if(strcmp(ext, "fs") == 0)
        {
            buff[count] = file_reader(p);
            printf("FRAGMENT SHADER: %s\nBUFF LOCATED AT: %p\nSTRING LOCATED AT: %p\n", buff[count], &buff[count], &buff[count][0]);
        }
        if(strcmp(ext, "vs") == 0)
        {
            buff[count] = file_reader(p);
            printf("VERTEX SHADER: %s\nBUFF LOCATED AT: %p\nSTRING LOCATED AT: %p\n", buff[count], &buff[count], &buff[count][0]);
        }

        count++;//needed if files > 2
    }

    closedir(dir);
/*TODO(nilou):
        1. mandarli allo step di compilazione giusto:
            immagina:
            u32 vertex_program = choose_f_type(VERTEX, buff[x]);
            choose_f_type(union Type t)
            {
                switch(t)
                {
                    case VERTEX: vertex_compile(x)
                    break;
                    .
                    .
                    .
                    default:
                }
            }
        come prendere il buff giusto?
        faccio un loop su buff? e.g.:
        while(buff != NULL)
        {
            /uparrow
            buff+1;
        }
        non credo sia giustissimo

        2. Come faccio a creare più vertex programs?
            mi serve un array? no
            ci pensa OpenGL? si, devo solo fare:
                AttachShader(vertex/fragment program)
            perchè è sequenziale sia compilare che linkare quindi posso farlo
*/

    u32 prog_ID = 0;
#if 0
    u32 vertex_program = 0;
    u32 fragment_program = 0;

    while(buff != NULL)
    {
        program = choose_f_type(VERTEX, buff);
        buff = buff + 1;
        program = choose_f_type(FRAGMENT, buff);
        buff = buff + 1;

        prog_ID = glCreateProgram();

        //GlAttachShader(prog_ID, vertex_program);
        //GlAttachShader(prog_ID, fragment_program);
        GlAttachShader(prog_ID, program);
        
        glLinkProgram(prog_ID);

        i32 success; char info_log[LOG_SIZE] = {0};
        glGetProgramiv(prog_ID, GL_LINK_STATUS, &success);
        if(success == GL_FALSE) 
        {
            glGetProgramInfoLog(prog_ID, sizeof(info_log), NULL, info_log);
            printf(BASH_RED("ERROR")": Could NOT LINK shader [INFO LOG]:%s\n", info_log);
        }
        printf(BASH_GREEN("SUCCESS")": LIKING phase completed:%s\n", info_log);

        vertex_data();

        //glDeleteShader(vertex_program);
        //glDeleteShader(fragment_program);
        glDeleteShader(program);
    }

#endif
    free(buff);
    buff=NULL;
    return(prog_ID);
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

    printf(BASH_GREEN("SUCCESS")": VERTEX shader compiled:%s\n", info_log);
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

    printf(BASH_GREEN("SUCCESS")": FRAGMENT shader compiled:%s\n", info_log);
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
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), (void*)(3 * sizeof(f32)));
    glEnableVertexAttribArray(1);
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
    
    fread(buffer, TEXT_SIZE, sizeof(char), f);
    buffer[TEXT_SIZE+1] = '\0';
    fclose(f);
    
    return(buffer);
}
