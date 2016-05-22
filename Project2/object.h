#pragma once

#include "glew.h"

class Object {
public:
	Object(float vertices[], int vertices_size, GLuint elements[], int elements_size);
public:
	float* vertices_;
	int vertices_size_;
	GLuint* elements_;
	int elements_size_;
};
