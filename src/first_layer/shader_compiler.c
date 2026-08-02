#include "../includes/base.h"
#include "../includes/internals.h"

u32 shader_compile(char* vertex_path, char* fragment_path);
u32 vertex_compile(const char* vertex_file);
u32 fragment_compile(const char* fragment_file);
char* file_reader(char* file);

u32 shader_compile(char* vertex_path, char* fragment_path)
{
    u32 prog_ID = 0;
    char* v_file = file_reader(vertex_path);
    char* f_file = file_reader(fragment_path);

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
    printf(BASH_GREEN("SUCCESS")": LIKING phase completed:%s\n", info_log);

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

char* file_reader(char* file)
{
    FILE* f = fopen(file, "r");
    if(f == NULL) printf(BASH_RED("ERROR")": Could NOT OPEN shader file at \n");

//check how many bytes if the file, by moving a "cursor"(file position indicator) the thenn 
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
