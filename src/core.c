#include "includes/base.h"
#include "includes/internals.h"
#include "includes/core.h"

static inline void hints(void);
GLFWwindow* create_window(i16 width, i16 height, char* window_name);
static inline void framebuffer_size_callback(GLFWwindow*, int width, int height);

GLFWwindow* create_window(i16 width, i16 height, char* window_name)
{
    hints();
    
    //principalmente alloco memoria di default e setto gli hint
    assert(glfwInit());
    void* windowed = NULL; void* share_with_other_w = NULL;
    
    //look at interals.h 520~
    GLFWwindow* window = glfwCreateWindow(width, height, window_name, windowed, share_with_other_w);
    if(window == NULL)
    {
        printf(BASH_RED("ERROR")": Could not create window\n");
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    assert( gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) );

    return window;
}
//unused attrib does not have a name
static inline void framebuffer_size_callback(GLFWwindow*, int width, int height)
{
    glViewport(0, 0, width, height);
}

static inline void hints(void)
{
    //info found on window.c 294~
    //default options and GL version, here i have a title bar and not other shanenegans
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
	glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);

    glfwWindowHintString(GLFW_WAYLAND_APP_ID, "obCel");
}

//USEFULL HINTS
/*
    //request alpha channel in the buffer so that compositor can use transparency
                                GLFW_TRANSPARENT_FRAMEBUFFER,
    //wait till next fram finishes drawing to then displaying it in full, not generating pix by pix
                                GLFW_DOUBLEBUFFER,
    //allows resizing with mouse
                                GLFW_RESIZABLE,
    //if it has standard OS things like title bar, max/min buttons
                                GLFW_DECORATED,
    //if starts with keyboard focus
                                GLFW_FOCUSED,
    //if floating - keep always on top
                                GLFW_FLOATING,
    //if starts max
                                GLFW_MAXIMIZED,
    //usefull if i want to make windows invisible setting it to false
                                GLFW_VISIBLE,
    //usefull with content_scale or when changing to a monitor with != DPI
                                GLFW_SCALE_TO_MONITOR, 
    //if the window is hidden at creation and later shown, determines whether it should automatically gain keyboard focus.
                                GLFW_FOCUS_ON_SHOW,
    //if the mouse can click things "under" current focused window
                                GLFW_MOUSE_PASSTHROUGH,
                                GLFW_CONTEXT_VERSION_MAJOR,
                                GLFW_CONTEXT_VERSION_MINOR,
                                GLFW_OPENGL_PROFILE,
                                GLFW_OPENGL_CORE_PROFILE,

                                GLFW_WAYLAND_APP_ID,
*/
