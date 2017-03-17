#include "utils.h"

#include <iostream>
// Include GLEW
#define GLEW_STATIC
#include <GL/glew.h>

int printOglErrors(char* file, int line) {
	GLenum glErr = glGetError();

	if(glErr != GL_NO_ERROR) {
		std::cout << "OpenGL error at file " << file << ", line " << line << " : " << gluErrorString(glErr) << std::endl;
		return -1;
	}
	return 0;
}

