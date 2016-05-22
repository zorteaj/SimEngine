#include "shader_mgr.h"

#include "vertex_shader.h"
#include "fragment_shader.h"

#include "SOIL.h"

#include <iostream>


ShaderMgr* ShaderMgr::shader_mgr_instance_ = nullptr;

ShaderMgr* ShaderMgr::instance()
{
	if (shader_mgr_instance_ == nullptr)
	{
		shader_mgr_instance_ = new ShaderMgr();
	}
	return shader_mgr_instance_;
}

ShaderMgr::ShaderMgr()
	:ready_(false)
{

}

ShaderMgr::~ShaderMgr()
{
	glDeleteProgram(shader_program_);
	glDeleteShader(fragment_shader_);
	glDeleteShader(vertex_shader_);
}

const bool& ShaderMgr::ready() const
{
	return ready_;
}

void ShaderMgr::init()
{
	create_shader();
}

void ShaderMgr::create_shader()
{
	create_vertex_shader();
	create_fragment_shader();
	build_shader_program();
	setup_attributes();
	ready_ = true;
}

const GLuint& ShaderMgr::shaderProgram() const
{
	return shader_program_;
}

void ShaderMgr::create_vertex_shader()
{
	vertex_shader_ = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader_, 1, &vertex_shader_string, NULL);
	glCompileShader(vertex_shader_);
}

void ShaderMgr::create_fragment_shader()
{
	fragment_shader_ = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader_, 1, &fragment_shader_string, NULL);
	glCompileShader(fragment_shader_);
}

void ShaderMgr::build_shader_program()
{
	check_for_errors();
	shader_program_ = glCreateProgram();
	glAttachShader(shader_program_, vertex_shader_);
	glAttachShader(shader_program_, fragment_shader_);
	glBindFragDataLocation(shader_program_, 0, "outColor");
	glLinkProgram(shader_program_);
	glUseProgram(shader_program_);
}

void ShaderMgr::setup_attributes()
{
	GLint position_attribute = glGetAttribLocation(shader_program_, "position");
	glVertexAttribPointer(position_attribute, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7, 0);
	glEnableVertexAttribArray(position_attribute);

	GLint color_attribute = glGetAttribLocation(shader_program_, "color");
	glVertexAttribPointer(color_attribute, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7, (void*)(sizeof(GLfloat) * 2));
	glEnableVertexAttribArray(color_attribute);

	GLint texture_attribute = glGetAttribLocation(shader_program_, "texcoord");
	glEnableVertexAttribArray(texture_attribute);
	glVertexAttribPointer(texture_attribute, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7, (void*)(sizeof(GLfloat) * 5));



	// TODO : Break this stuff out 
	GLuint textures[2];
	glGenTextures(2, textures);

	int width, height;
	unsigned char* image;

	//------------------------------------------------------------------
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	image = SOIL_load_image("siding.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glUniform1i(glGetUniformLocation(shader_program_, "texFrog"), 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//------------------------------------------------------------------


	//------------------------------------------------------------------
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	image = SOIL_load_image("frog.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glUniform1i(glGetUniformLocation(shader_program_, "texFox"), 1);

	// What to do when the texture image is smaller than the polygon onto which it's mapped (I think)
	// We're clamping to edge
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Apply filtering (for when texture coordinates don't match a pixel perfectly)
	// Linear is a weighted averaged of 4 surrounding pixels
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//------------------------------------------------------------------
}

void ShaderMgr::check_for_errors()
{
	GLint vertex_shader_status;
	glGetShaderiv(vertex_shader_, GL_COMPILE_STATUS, &vertex_shader_status);
	if (vertex_shader_status != GL_TRUE)
	{
		char buffer[512];

		glGetShaderInfoLog(vertex_shader_, 512, NULL, buffer);
		std::cerr << "Vertex Shader failed to compile: " << buffer << std::endl;
	}

	GLint fragment_shader_status;
	glGetShaderiv(fragment_shader_, GL_COMPILE_STATUS, &fragment_shader_status);
	if (fragment_shader_status != GL_TRUE)
	{
		char buffer[512];

		glGetShaderInfoLog(fragment_shader_, 512, NULL, buffer);
		std::cerr << "Fragment Shader failed to compile: " << buffer << std::endl;
	}
}

