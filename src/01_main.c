#include "00_includes/00_base.h"
#include "00_includes/01_internals.h"
#include "00_includes/02_core.h"
#include "00_includes/01_first_layer/01_backgorund.h"
#include "00_includes/01_first_layer/02_shader_compiler.h"

//for platorm specific things look into platform.h
int main(void)
{
    i16 WIDTH = 800;
    i16 HEIGHT = 800;
    GLFWwindow* window = create_window(WIDTH, HEIGHT, "obCel");
    i8 r = 16; i8 g = 71; i8 b = 83; f32 alpha = 1.0f;
    
    shader_compile("src/01_first_layer/00_shaders/02_rectangle/01_rec_ver.vs","src/01_first_layer/00_shaders/02_rectangle/02_rec_frag.fs");
    
    while(!glfwWindowShouldClose(window)) 
    {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE)) glfwSetWindowShouldClose(window, true);
        set_background(r,g,b,alpha);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    printf(BASH_GREEN("SUCCESS")": window closed successfully\n");
    exit(EXIT_SUCCESS);
}
