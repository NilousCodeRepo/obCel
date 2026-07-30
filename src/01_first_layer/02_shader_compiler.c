#include "../00_includes/00_base.h"
#include "../00_includes/01_internals.h"

u32 shader_compile(const char* vertex_path, const char* fragment_path);
u32 vertex_compile(const char* vertex_file);
u32 fragment_compile(const char* fragment_file);
const char* file_reader(const char* file);

u32 shader_compile(const char* vertex_path, const char* fragment_path)
{
    u32 prog_ID = 0;
    const char* v_file = file_reader(vertex_path);
    const char* f_file = file_reader(fragment_path);

    //printf("VERTEX FILE: \n %s \n\nFRAGMENT FILE: \n %s \n", v_file, f_file);

    u32 vertex_program = vertex_compile(v_file);
    u32 fragment_program = fragment_compile(f_file);

    prog_ID = glCreateProgram();

    glAttachShader(prog_ID, vertex_program);
    glAttachShader(prog_ID, fragment_program);
    
    glLinkProgram(prog_ID);

    i32 success; char info_log[LOG_SIZE] = {0};
    glGetShaderiv(prog_ID, GL_LINK_STATUS, &success);
    if(success == GL_FALSE) 
    {
        glGetShaderInfoLog(prog_ID, sizeof(info_log), NULL, info_log);
        printf(BASH_RED("ERROR")": Could NOT LINK shader [INFO LOG]:%s\n", info_log);
    }
    free(v_file);
    free(f_file);

    glDeleteShader(vertex_program);
    glDeleteShader(fragment_program);

    return(prog_ID);
}

u32 vertex_compile(const char* vertex_file)
{
    u32 vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_file, NULL);

    i32 success; char info_log[LOG_SIZE] = {0};
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if(success == GL_FALSE) 
    {
        glGetShaderInfoLog(vertex_shader, sizeof(info_log), NULL, info_log);
        printf(BASH_RED("ERROR")": Could NOT COMPILE vertex shader [INFO LOG]:%s\n", info_log);
    }

    return(vertex_shader);
}

u32 fragment_compile(const char* fragment_file)
{
    u32 fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_file, NULL);

    i32 success; char info_log[LOG_SIZE] = {0};
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if(success == GL_FALSE) 
    {
        glGetShaderInfoLog(fragment_shader, sizeof(info_log), NULL, info_log);
        printf(BASH_RED("ERROR")": Could NOT COMPILE fragment shader [INFO LOG]:%s\n", info_log);
    }

    return(fragment_shader);
}

const char* file_reader(const char* file)
{
    FILE* f = fopen(file, "r");
    if(f == NULL) printf(BASH_RED("ERROR")": Could NOT OPEN shader file at \n");

//check how many bytes if the file, by moving a "cursor"(file position indicator) the thenn 
//reset the "cursor" position in the file
    fseek(f, 0, SEEK_END); 
    u16 size = ftell(f); 
    fseek(f, 0, SEEK_SET);

    const char* buffer = (const char*) malloc(size + 1);
    if(buffer == NULL)printf(BASH_RED("ERROR")": ALLOCATION of buffer for shader compilation failed\n");
    
    fread(buffer, size, sizeof(char), f);
    
    printf(BASH_YELLOW("%s")"\n", buffer);

    fclose(f);
    return(buffer);
}
