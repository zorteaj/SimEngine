#pragma once

#include "SDL.h"
#include "glew.h"
#include "glm.hpp"

class Object;
class ShaderMgr;

class Engine
{
public:
	Engine();
	~Engine();
	SDL_Window* window();
	void tick();
	const bool& quit() const;
	void add_object(const Object& obj);
private:
	void setup_sdl();
	void setup_opengl();
	void create_window();
	void setup_vertices_and_elements(const Object& obj);
	void setup_vertices(float vertices[], int size);
	void setup_elements(GLuint elements[], int size);
private:
	SDL_Window* window_;
	SDL_GLContext context_;
	ShaderMgr* shader_mgr_;
	bool quit_;
	GLuint vertex_array_object_;
	GLuint vertex_obj_buffer_;
	GLuint elements_buffer_object_;
	glm::vec3* eye_;
	glm::vec3* center_;
};