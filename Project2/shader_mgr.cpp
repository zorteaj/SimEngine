#include "shader_mgr.h"

#include "vertex_shader.h"
#include "fragment_shader.h"

#include <iostream>

ShaderMgr::ShaderMgr()
{

}

ShaderMgr::~ShaderMgr()
{
	glDeleteProgram(shader_program);
	glDeleteShader(fragment_shader);
	glDeleteShader(vertex_shader);
}

void ShaderMgr::create_shader()
{
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_string, NULL);
	glCompileShader(vertex_shader);
	GLint vertex_shader_status;
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &vertex_shader_status);
	if (vertex_shader_status != GL_TRUE)
	{
		char buffer[512];

		glGetShaderInfoLog(vertex_shader, 512, NULL, buffer);
		std::cerr << "Vertex Shader failed to compile: " << buffer << std::endl;
	}

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_string, NULL);
	glCompileShader(fragment_shader);
	GLint fragment_shader_status;
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &fragment_shader_status);
	if (fragment_shader_status != GL_TRUE)
	{
		char buffer[512];

		glGetShaderInfoLog(fragment_shader, 512, NULL, buffer);
		std::cerr << "Fragment Shader failed to compile: " << buffer << std::endl;
	}

	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glBindFragDataLocation(shader_program, 0, "outColor");
	glLinkProgram(shader_program);
	glUseProgram(shader_program);

	GLint position_attribute = glGetAttribLocation(shader_program, "position");
	glVertexAttribPointer(position_attribute, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glEnableVertexAttribArray(position_attribute);

	GLint color_attribute = glGetAttribLocation(shader_program, "color");
	glVertexAttribPointer(color_attribute, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 2));
	glEnableVertexAttribArray(color_attribute);
}
