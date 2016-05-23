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
	void setup_textures();
	void setup_siding_texture();
	void setup_frog_texture();
private:
	static ShaderMgr* shader_mgr_instance_;
	GLuint shader_program_;
	GLuint fragment_shader_;
	GLuint vertex_shader_;
	GLuint textures_[2];
	bool ready_;
};