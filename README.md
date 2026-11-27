###### TODO:
- [ ] Debug ts 
- [ ] Create procedure to read mesh.h file and automatically instance or add to VBO and create VAO and EBO
- [ ] same as above for shaders 
- [ ] implement cleanup of resources
- [ ] Search and use some sort of debug info for opengl
- [ ] Make a button
- [ ] Make the button react on click(color becomes darker)
- [ ] REJOICE YOU ARE HALFWAY THERE
- [ ] Make the Makefile separate DEBUG and RELEASE version
- [ ] create system to compile shader once and call them with a func like "compile_shader(path_file.txt)"
###### MAYBE:
- [ ] make script to check gl version and auto generate glad, base and include/not-include deprecated things
- [ ] check if clang makes your job better
###### INFO:
- transparency exists as frambuffer && window parameter, but using only one is undef bev
- An OGL context seems to be the running process more or less

###### IDEAS:

- For mesh value reading:

    does every vertex file need it's vertices? yes.

    should i write code for every vert coord? no. I will program some basic shapes and mod them

    point = 1 2 0
    point 2 = point one but with 1+1 2+0 0+0

    Do i have to write things like:
    drawTriangle(pos)
    ?
    How would this interface itself with a more complex senario in a data movement sense?
    do i need things like squircles and rounded corners rectangle? yes
