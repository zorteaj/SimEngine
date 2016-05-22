#pragma once

#include "glew.h"

class ShaderMgr
{
public:
	ShaderMgr();
	~ShaderMgr();
	void create_shader();
	void clean_up();
private:
	GLuint shader_program;
	GLuint fragment_shader;
	GLuint vertex_shader;
};