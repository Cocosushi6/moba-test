#ifndef MESH_H
#define MESH_H

#include <iostream>
// Include GLEW
#include <GL/glew.h>

// Include GLFW

#include <vector>
#include <string>

#include "shader.h"

struct MeshVertex { // A point in the world
	glm::vec3 Position;
	glm::vec3 Normals;
	glm::vec2 TexCoords;
};

struct Texture {
	GLuint id;
	std::string type; //specular, diffuse, etc.
	std::string path;
};

class Mesh {
public:
	std::vector<MeshVertex> vertices; //vertices for VBOs
	std::vector<GLuint> indices; //indices for EBOs
	std::vector<Texture> textures; //Texture coordinates & al

	Mesh(std::vector<MeshVertex> pVertices, std::vector<GLuint> indices, std::vector<Texture> textures);
	void draw(Shader shad);
private:
	GLuint VAO, VBO, EBO;
	void setupMesh();
};

#endif
