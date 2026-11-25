#pragma once

u32 vertex_compile(const char*);
u32 fragment_compile(const char*);
u32 shader_compile(const char*);

const char *get_filename_ext(const char*);
char* file_reader(char*);

void vertex_data(void);
