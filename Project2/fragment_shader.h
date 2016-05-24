#pragma once

#pragma once

#include "glew.h"

// This is our fragment shader program, which is in a string format, to avoid having to load from a file

// The otuput of this program is the final color of the fragment

// This color can be determined from the vertex color, texture coordintates, or whatever
// other data coming from the vertex shader

const GLchar* fragment_shader_string =
"#version 150 core\n"

"in vec3 Color;"
"in vec2 Texcoord;"

"out vec4 outColor;"

"uniform sampler2D texFrog;"
"uniform sampler2D texFox;"

"void main()"
"{"
"	vec4 texColor = mix(texture(texFrog, Texcoord), texture(texFox, Texcoord), 0.85);"
"	outColor = vec4(Color, 1.0) * texColor;"
"}";