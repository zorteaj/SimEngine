#include "engine.h"

#include "shader_mgr.h"
#include "object.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include <map>
#include <iostream>

Engine::Engine()
{
	setup_sdl();
	create_window();
	setup_opengl();
	shader_mgr_ = ShaderMgr::instance();
}

Engine::~Engine()
{
	SDL_GL_DeleteContext(context_);
	glDeleteBuffers(1, &vertex_obj_buffer_);
	glDeleteVertexArrays(1, &vertex_array_object_);
	SDL_Quit();
	SDL_DestroyWindow(window_);
	window_ = NULL;
}

void Engine::tick()
{
	if (!shader_mgr_->ready())
	{
		shader_mgr_->init();
	}

	enum Mode
	{
		OBJ_ROLL,
		CAM_CENTER_Z
	} mode;

	mode = OBJ_ROLL;

	std::map<Mode, float> mode_map;
	mode_map[OBJ_ROLL] = 180.0;
	mode_map[CAM_CENTER_Z] = 0.0;

	SDL_Event event;
	while (!quit_)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit_ = true;
			}
			else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					quit_ = true;
					break;
				case SDLK_o:
					mode = OBJ_ROLL;
					break;
				case SDLK_z:
					mode = CAM_CENTER_Z;
				default:
					break;
				}
			}
			else if (event.type == SDL_MOUSEWHEEL)
			{
				if (mode == OBJ_ROLL)
				{
					mode_map[OBJ_ROLL] = (int)(mode_map[OBJ_ROLL] + event.wheel.y) % 360;
				}
				else if (mode == CAM_CENTER_Z)
				{
					mode_map[CAM_CENTER_Z] += (event.wheel.y * 0.1);
				}

			}
		}

		glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 model;
		model = glm::rotate(model, glm::radians(mode_map[OBJ_ROLL]), glm::vec3(0.0f, 0.0f, 1.0f)); // *glm::translate(model, glm::vec3(1.0f, 1.0f, 1.0f));
		GLint uniform_transformation = glGetUniformLocation(shader_mgr_->shaderProgram(), "model");
		glUniformMatrix4fv(uniform_transformation, 1, GL_FALSE, glm::value_ptr(model));

		// eye, center, up
		glm::mat4 view = glm::lookAt(
			glm::vec3(0.0f, 6.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, mode_map[CAM_CENTER_Z]),
			glm::vec3(0.0f, 0.0f, 1.0f)
			);
		GLuint uniform_view = glGetUniformLocation(shader_mgr_->shaderProgram(), "view");
		glUniformMatrix4fv(uniform_view, 1, GL_FALSE, glm::value_ptr(view));

		glm::mat4 proj = glm::perspective(glm::radians(45.0f), 640.0f / 640.0f, 1.0f, 10.0f);
		GLuint uniform_projection = glGetUniformLocation(shader_mgr_->shaderProgram(), "proj");
		glUniformMatrix4fv(uniform_projection, 1, GL_FALSE, glm::value_ptr(proj));

		//glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		SDL_GL_SwapWindow(window_);
	}
}

const bool& Engine::quit() const
{
	return quit_;
}

void Engine::setup_sdl()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cerr << "Error initalizing SDL: " << SDL_GetError() << std::endl;
	}
}

void Engine::setup_opengl()
{
	context_ = SDL_GL_CreateContext(window_);
	if (context_ == NULL) {
		std::cerr << "OpenGL context could not be created: " << SDL_GetError() << std::endl;
	}

	glewExperimental = GL_TRUE;
	GLenum glew_state = glewInit();

	if (glew_state != GLEW_OK)
	{
		std::cerr << "Glew failed to initialize: " << glewGetErrorString(glew_state) << std::endl;
	}

	glEnable(GL_DEPTH_TEST);

	glGenVertexArrays(1, &vertex_array_object_);
	glBindVertexArray(vertex_array_object_);
}

void Engine::add_object(const Object& obj)
{
	setup_vertices_and_elements(obj);
}

void Engine::create_window()
{
	window_ = SDL_CreateWindow("ZORG",
		100, 100,
		640, 640,
		SDL_WINDOW_OPENGL);
}

SDL_Window* Engine::window()
{
	return window_;
}

void Engine::setup_vertices_and_elements(const Object& obj)
{
	setup_vertices(obj.vertices_, obj.vertices_size_);
	setup_elements(obj.elements_, obj.elements_size_);
}

void Engine::setup_vertices(float vertices[], int size)
{
	glGenBuffers(1, &vertex_obj_buffer_);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_obj_buffer_);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void Engine::setup_elements(GLuint elements[], int size)
{
	glGenBuffers(1, &elements_buffer_object_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements_buffer_object_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, elements, GL_STATIC_DRAW);
}
