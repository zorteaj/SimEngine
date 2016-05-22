#pragma once

#include "glew.h"

class ShaderMgr
{
public:
	static ShaderMgr* instance();
	~ShaderMgr();
	void init();
	const bool& ready() const;
	const GLuint& shaderProgram() const;
private:
	ShaderMgr();
	void create_shader();
	void create_vertex_shader();
	void create_fragment_shader();
	void build_shader_program();
	void setup_attributes();
	void check_for_errors();
private:
	static ShaderMgr* shader_mgr_instance_;
	GLuint shader_program_;
	GLuint fragment_shader_;
	GLuint vertex_shader_;
	bool ready_;
};