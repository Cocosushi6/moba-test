#ifndef SRC_UTILS_H
#define SRC_UTILS_H

#include <iostream>
// Include GLEW
#define GLEW_STATIC
#include <GL/glew.h>

int printOglErrors(char* file, int line);


#define printOpenGLError() printOglErrors(__FILE__, __LINE__);

#endif
