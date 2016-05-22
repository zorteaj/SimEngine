#include "engine.h"

#include "object.h"

#include <iostream>

Engine::Engine()
{
	setup_sdl();
	create_window();
	setup_opengl();
}

Engine::~Engine()
{
	// TODO : Make context member if possible
	//SDL_GL_DeleteContext(context);
	glDeleteBuffers(1, &vertex_obj_buffer_);
	glDeleteVertexArrays(1, &vertex_array_object_);
	SDL_Quit();
	SDL_DestroyWindow(window_);
	window_ = NULL;
}

void Engine::tick()
{
	SDL_Event event;
	while (!quit_)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit_ = true;
			}
		}

		glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
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
	SDL_GLContext context = SDL_GL_CreateContext(window_);
	if (context == NULL) {
		std::cerr << "OpenGL context could not be created: " << SDL_GetError() << std::endl;
	}

	glewExperimental = GL_TRUE;
	GLenum glew_state = glewInit();

	if (glew_state != GLEW_OK)
	{
		std::cerr << "Glew failed to initialize: " << glewGetErrorString(glew_state) << std::endl;
	}
}

void Engine::add_object(const Object& obj)
{
	setup_vertices_and_elements(obj);
}

void Engine::create_window()
{
	window_ = SDL_CreateWindow("ZORG",
		100, 100,
		640, 480,
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
	glGenVertexArrays(1, &vertex_array_object_);
	glBindVertexArray(vertex_array_object_);

	glGenBuffers(1, &vertex_obj_buffer_);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_obj_buffer_);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void Engine::setup_elements(GLuint elements[], int size)
{
	GLuint elements_buffer_object;
	glGenBuffers(1, &elements_buffer_object);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements_buffer_object);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, elements, GL_STATIC_DRAW);
}
