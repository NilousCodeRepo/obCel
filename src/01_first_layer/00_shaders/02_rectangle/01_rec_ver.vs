#version 460 core
layout (location = 0) in vec3 aPos;

void main()
{
    //here aPos will take the values of the vertices i believe
    //gl_Position is predefined in GLSL, notice no data type
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);
}
