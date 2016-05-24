#pragma once

#pragma once

#include "glew.h"

// This is our vertex shader program, which is in a string format, to avoid having to load from a file

// The output of this program is the vertex position

// The vertex shader is a program on the grahpics card that processes each vertex and its attributes
// as they appear in the vertex array.  Its duty is to output the final vector position in device
// coordinates and to output any data the fragment shader requires.  That's why the 3D transformation
// should take place here.

const GLchar* vertex_shader_string =
"#version 150 core\n"

"in vec3 position;"
"in vec3 color;"
"in vec2 texcoord;"

"out vec3 Color;"
"out vec2 Texcoord;"

"uniform mat4 model;"
"uniform mat4 view;"
"uniform mat4 proj;"

"void main()"
"{"
"    Color = color;"
"    Texcoord = texcoord;"
"    gl_Position = proj * view * model * vec4(position, 1.0);"
"}";