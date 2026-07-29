#include "../00_includes/00_base.h"
#include "../00_includes/01_internals.h"

u32 shader_compile(char* vertex_path, char* fragment_path);

u32 shader_compile(char* vertex_path, char* fragment_path)
{
    u32 prog_ID = 0;

//==== VERTEX SHADER ====
    FILE* vertex_file = fopen(vertex_path, "r");
    if(vertex_file == NULL) printf(BASH_RED("ERROR")":Could not open Vertex Shader file at %s\n", vertex_path);

//check how many bytes if the file, by moving a "cursor"(file position indicator) the thenn 
//reset the "cursor" position in the file
    fseek(vertex_file, 0, SEEK_END); 
    u16 verf_size = ftell(vertex_file); 
    fseek(vertex_file, 0, SEEK_SET);
//TODO(nilou): create function to read file that returns const char* and ret buffer from there
    const GLchar* const vf_buffer = (const GLchar* const) malloc(verf_size + 1);
    if(vf_buffer == NULL)printf(BASH_RED("ERROR")":Allocation of buffer for shader compilation failed\n");
    
    fread(vf_buffer, verf_size, sizeof(char), vertex_file);
    
//ora vf_buffer contiene il programma da compilare

    u32 vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vf_buffer, NULL);

    i32 success; char info_log[512] = {0};
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if(!success == GL_FALSE) 
    {
        glGetShaderInfoLog(vertex_shader, sizeof(info_log), NULL, info_log);
        printf("[ERROR]: Could NOT COMPILE VERTEX shader\n[INFO LOG]:%s", info_log);
    }


//=======================

//==== FRAGMENT SHADER ====
    FILE* fragment_file = fopen(fragment_path, "r");
    if(fragment_file == NULL) printf(BASH_RED("ERROR")":Could not open Fragment Shader file at %s\n",fragment_path);

    fseek(fragment_file, 0, SEEK_END); 
    u16 fragf_size = ftell(fragment_file); 
    fseek(fragment_file, 0, SEEK_SET);
    
    char* ff_buffer = (char*) malloc(verf_size + 1);
    if(ff_buffer == NULL)printf(BASH_RED("ERROR")":Allocation of buffer for shader compilation failed\n");
    
    fread(ff_buffer, fragf_size, sizeof(char), fragment_file);
//========================
    fclose(vertex_file);
    fclose(fragment_file);
    free(vf_buffer);
    free(ff_buffer);

    return(prog_ID);
}


