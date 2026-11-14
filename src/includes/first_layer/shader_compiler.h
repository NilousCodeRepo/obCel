#pragma once

u32 choose_f_type(Type t, const char**);
u32 shader_compile(const char*);
u32 vertex_compile(const char*);
u32 fragment_compile(const char*);

void vertex_data(void);

const char *get_filename_ext(const char*);
char* file_reader(char*);
