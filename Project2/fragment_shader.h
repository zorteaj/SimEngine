#pragma once

#pragma once

#include "glew.h"

// This is our fragment shader program, which is in a string format, to avoid having to load from a file

// The otuput of this program is the final color of the fragment

// This color can be determined from the vertex color, texture coordintates, or whatever
// other data coming from the vertex shader

// Our program just makes every fragment white

/*
#version 150

out vec4 outColor;

void main()
{
// There's no special gl_* variable here, because we can output multiple colors
outColor = vec4(1.0, 1.0, 1.0, 1.0);
}
*/

// we can toggle here in the shader whether to use the uniform of in Color
const GLchar* fragment_shader_string =
"#version 150 core\n"
"uniform vec3 triangleColor;"
"in vec3 Color;"
"out vec4 outColor;"
"void main()"
"{"
"    outColor = vec4(Color, 1.0);"
"}";
