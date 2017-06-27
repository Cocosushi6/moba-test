/*
 * shader.h
 *
 *  Created on: Jan 15, 2017
 *      Author: sacha
 */

#ifndef SRC_SHADER_H_
#define SRC_SHADER_H_

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <GL/glew.h>

class Shader
{
	public:
		GLuint programID;

		Shader(const char* vertexPath, const char* fragmentPath);
		int load();
		void use();

	private:
		const char* vertexPath;
		const char* fragmentPath;

};


#endif /* SRC_SHADER_H_ */
