#include "includes/base.h"
#include "includes/internals.h"
#include "includes/core.h"
#include "includes/first_layer/background.h"
#include "includes/first_layer/shader_compiler.h"

//for platorm specific things look into platform.h
int main(void)
{
    i16 WIDTH = 800;
    i16 HEIGHT = 800;
    GLFWwindow* window = create_window(WIDTH, HEIGHT, "obCel");
    i8 r = 16; i8 g = 71; i8 b = 83; f32 alpha = 1.0f;
    
    u32 program = shader_compile("src/first_layer/shaders/triangle/rec_ver.vs","src/first_layer/shaders/triangle/rec_frag.fs");

    while(!glfwWindowShouldClose(window)) 
    {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE)) glfwSetWindowShouldClose(window, true);
        set_background(r,g,b,alpha);

        glUseProgram(program);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    printf(BASH_GREEN("SUCCESS")": window closed successfully\n");
    exit(EXIT_SUCCESS);
}
