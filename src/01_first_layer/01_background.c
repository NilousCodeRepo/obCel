#include <stdio.h>
#include "../00_includes/00_base.h"

void set_background(i8 r, i8 g, i8 b, f32 alpha)
{
    //greenish bg
    if(alpha > 1.0f || alpha < 0.0f) alpha = 1.0f;

    glClearColor(r/255.0, g/255.0, b/255.0, alpha);
    glClear(GL_COLOR_BUFFER_BIT);
}

#if 0
    f16 x = 50 / 100.0f;
    f16 y = 50 /100.0f;
    f16 z = 0.0f;

    //button vertices
    f16 vertices[] =
    {
        -x,  y, z, // left high
        -x, -y, z, // left low

         x,  y, z, // right high
        -x, -y, z  // right low
    };

   /*
    * vertex buffer object is the address of the first byte of the memory
    * to where the buffers ID will be stored then
    * we GL will pass the buffers to the GPU's VRAM
    */
    u32 VBO;
    
    //ret ID for 1 VBO not a buffer object yet
    glGenBuffers(1, &VBO);

    //bind that specific VBO to a "GL_ARRAY_BUFFER" data type to make it a real buffer name
    //still no memory allocated to it. but it is a buffer object
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    //here i finally allocate memory for my VBO
    //now every op on this target(GL_ARRAY_BUFFER) will be made in the VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
                                                            /*here i say to use
                                                             * the same data
                                                             * many times
                                                             */
    //I create the ID for my vertex shader object
    u32 vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    //here i pass the ID, 1 is string count
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    
    i32 success;
    char info_log[512] = {0};
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if(!success == GL_FALSE) 
    {
        glGetShaderInfoLog(vertex_shader, sizeof(info_log), NULL, info_log);
        printf("[ERROR]: Could NOT COMPILE VERTEX shader\n[INFO LOG]:%s", info_log);

    }

    u32 fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if(!success == GL_FALSE) 
    {
        glGetShaderInfoLog(fragment_shader, sizeof(info_log), NULL, info_log);
        printf("[ERROR]: Could NOT COMPILE FRAGMENT shader\n[INFO LOG]:%s", info_log);
    }

    //not i have the binary of the shaders in my VRAM
    //i have now to link them and execute them
 
    //here i create an ID which the final shader program will point
    u32 shader_program = glCreateProgram();
    //we have to pass them in the correct order(the pipeline one i believe)
    //so that outs -> ins and so on
    //here i say what programs to link and compose to create the finale shader_program
    glAttachShader(shader_program ,vertex_shader);
    glAttachShader(shader_program ,fragment_shader);
    glLinkProgram(shader_program);

    glGetShaderiv(shader_program, GL_LINK_STATUS, &success);
    if(!success == GL_FALSE) 
    {
        glGetShaderInfoLog(shader_program, sizeof(info_log), NULL, info_log);
        printf("[ERROR]: Could NOT LINK shaders\n[INFO LOG]:%s", info_log);
    }
    
    //freeing some memory
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    //it installs the program object specified by program as part of current rendering state
    //ogni chiamata alle shader e al rendering userà questo programma.
    glUseProgram(shader_program);
    
    //Dobbiamo passare al programma i vertici che abbiamo creato
    //e che sono bound al nostro VBO corrente
    
    u8 position = 0; //same as in the shader
    u8 size = 4; //number of elements, max 4
    i32 data_type = GL_FLOAT;
    b1 to_normalize = GL_FALSE;
    u32 stride = sizeof(f32) * 4;
    void* first_offset = 0;

    glVertexAttribPointer(position,
                          size,
                          data_type, 
                          to_normalize,
                          stride,
                          first_offset
                         );
    glEnableVertexAttribArray(position);
#endif
