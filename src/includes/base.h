//#ifndef BASE_H
//#define BASE_H
#pragma once
#include <glad.h>

typedef GLbyte   i8;
typedef GLshort  i16;
typedef GLint    i32;
typedef GLint64  i64;

typedef GLubyte  u8;
typedef GLushort u16;
typedef GLuint   u32;
typedef GLuint64 u64;

typedef GLhalf   f16;//actually an u16 from khronos_uint16_t which is a u16
typedef GLfloat  f32;
typedef GLclampf cf32;//value between [0..1]
typedef GLdouble f64;

typedef GLintptr  size_p;
typedef GLenum    u32;
typedef GLsizei   i32;
typedef GLboolean b1;
//#endif
