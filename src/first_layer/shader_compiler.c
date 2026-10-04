#define _DEFAULT_SOURCE //needed for DT_xxx macros in C > C99
#include "../includes/base.h"
#include "../includes/internals.h"

u32 shader_compile(const char* path);
u32 vertex_compile(const char* vertex_file);
u32 fragment_compile(const char* fragment_file);

void vertex_data(void);

const char *get_filename_ext(const char *filename);
char* file_reader(char* file);

#define BUFF_SIZE 249

u32 shader_compile(const char* path)
{
    u32 prog_ID = 0;
    DIR* dir;
    struct dirent* entry;
    char* buff = NULL;
    
    if((dir = opendir(path)) == NULL)
    {
        printf(BASH_RED("ERROR")": Could not open folder\n");
        return(1);
    }

    while((entry = readdir(dir)) != NULL)
    {
        char p[BUFF_SIZE];

        //serve saltare l'attuale cartella, sennò ricorsione infinita ed errore
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        //sto creando la stringa che equivale al path
        snprintf(p, sizeof(p), "%s/%s", path, entry->d_name);

        if(entry->d_type == DT_DIR) shader_compile(p);

        char ext[8];
        snprintf(ext, sizeof(ext), "%s", get_filename_ext(entry->d_name));
        
        if(strcmp(ext, "vs") == 0 || strcmp(ext, "fs") == 0)
        {
            buff = file_reader(p);//ricorda di buff=NULL appena puoi.
        }
    }
    
    }
    closedir(dir);
/*
    ora i file li apre e li stampa, ora devo:
        1. stamparli in un buffer
        2. farmi mandare una tupla di valori, buffer address and buffer size
           direttamente da file_reader();
        3. ogni size lo divido in ogni buffer di buffer, con in mezzo un "\"
        4. copiarli ogni volta in un altro buffer fino a "\"
        5. mandarli allo step di compilazione giusto
*/

#if 0
    char* v_file = file_reader(vertex_path);
    char* f_file = file_reader(fragment_path);

    u32 vertex_program = vertex_compile(v_file);
    u32 fragment_program = fragment_compile(f_file);

    prog_ID = glCreateProgram();

    glAttachShader(prog_ID, vertex_program);
    glAttachShader(prog_ID, fragment_program);
    
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

    free(v_file);
    free(f_file);

    glDeleteShader(vertex_program);
    glDeleteShader(fragment_program);
#endif
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
    u16 size = ftell(f); 
    fseek(f, 0, SEEK_SET);

    char* buffer = (char*) malloc(size + 1);
    if(buffer == NULL)printf(BASH_RED("ERROR")": ALLOCATION of buffer for shader compilation failed\n");
    
    fread(buffer, size, sizeof(char), f);
    buffer[size] = '\0';
    fclose(f);
    return(buffer);
}
