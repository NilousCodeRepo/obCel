###### TODO:
- [x] Make a background
- [x] Create base.h
- [x] Change types to "base types"
- [x] Change types to GL types
- [x] move shaders in their on files
- [x] create procedures to read shaders
- [x] in shader_compile file, make a func for every shader type
- [x] check TODOs
- [x] write actuall shader code to make them work
- [x] remove -Wdiscarded-qualifiers warnings
- [x] remove number prefix from files and regenerate tags
- [x] Separate the creation of VBO and VAO from shader creation
- [ ] Using:
        https://github.com/JoeyDeVries/LearnOpenGL/blob/master/src/1.getting_started/2.5.hello_triangle_exercise3/hello_triangle_exercise3.cpp
        make the program better, it should do what does here, but more general and with the style of the program
- [ ] Create procedure to read mesh.h file and automatically instance or add to VBO and create VAO and EBO
- [ ] same as above for shaders 
- [ ] implement cleanup of resources
- [ ] Search and use some sort of debug info for opengl
- [ ] Make a button
- [ ] Make the button react on click(color becomes darker)
- [ ] REJOICE YOU ARE HALFWAY THERE
- [ ] Remake makefile so that it's simpler and does not -Iglfw for everything, becauser -I looks up the dirs so it slows down compilation
- [ ] Make the Makefile separate DEBUG and RELEASE version
- [ ] create system to compile shader once and call them with a func like "compile_shader(path_file.txt)"
###### MAYBE:
- [ ] make script to check gl version and auto generate glad, base and include/not-include deprecated things
###### INFO:
- transparency exists as frambuffer && window parameter, but using only one is undef bev
- An OGL context seems to be the running process more or less
