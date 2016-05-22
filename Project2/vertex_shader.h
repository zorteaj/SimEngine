#pragma once

#pragma once

#include "glew.h"

// This is our vertex shader program, which is in a string format, to avoid having to load from a file

// The output of this program is the vertex position

// The vertex shader is a program on the grahpics card that processes each vertex and its attributes
// as they appear in the vertex array.  Its duty is to output the final vector position in device
// coordinates and to output any data the fragment shader requires.  That's why the 3D transformation
// should take place here.

// Since the vertex positions we're passing in are already specified in device coordinates, and no other
// atrributes exist, this vertex shader is bare bones

/*
#version 150

// our attribute
// values in attributes are always floats
// the number of the vector (2 in this case) specifies the number of components in the attribute
in vec2 position;

void main()
{
// this is a special variable. i'm not sure what they 3rd and 4th arguments are,
// but the 4th needs to be 1.0 for some reason.  the rest are supposedly free to
// be messed with
gl_Position = vec4(position, 0.0, 1.0);
}
*/

const GLchar* vertex_shader_string =
"#version 150 core\n"

"in vec2 position;"
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
"    gl_Position = proj * view * model * vec4(position, 0.0, 1.0);"
"}";