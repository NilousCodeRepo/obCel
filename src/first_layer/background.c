#include <stdio.h>
#include "../includes/base.h"

void set_background(i8 r, i8 g, i8 b, f32 alpha)
{
    //greenish bg
    if(alpha > 1.0f || alpha < 0.0f) alpha = 1.0f;

    glClearColor(r/255.0, g/255.0, b/255.0, alpha);
    glClear(GL_COLOR_BUFFER_BIT);
}
