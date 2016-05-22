// https://open.gl/drawing

#include "object.h"
#include "engine.h"
#include "shader_mgr.h"

#include "SDL.h"
#include "glew.h"

#include <iostream>

int main(int argc, char *argv[])
{
	Engine engine;
	
	float vertices[] = {
		-0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
		0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f
	};

	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0,
		0, 4, 1,
		0, 5, 1
	};

	Object obj(vertices, sizeof(vertices), elements, sizeof(elements));
	engine.add_object(obj);

	while (!engine.quit())
	{
		engine.tick();
	}

	return 0;
}
