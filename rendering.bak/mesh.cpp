//include GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>
// Include GLFW
// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <string>

#include "shader.h"
#include "mesh.h"
#include "utils/utils.h"

Mesh::Mesh(std::vector<MeshVertex> vertices) {
	this->vertices = vertices;
	this->setupMesh();
}

Mesh::Mesh(std::vector<MeshVertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures) {
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	VAO = 0;
	VBO = 0;
	EBO = 0;

	this->setupMesh();
}

void Mesh::setupMesh() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//if mesh is initialised with indices (depends on used constructor)
	if(indices.size() != 0) {
		glGenBuffers(1, &EBO);
	}

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(MeshVertex), &this->vertices[0], GL_STATIC_DRAW);

	if(indices.size() != 0) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);
	}

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (GLvoid*)0);

	if(indices.size() != 0) {
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (GLvoid*)offsetof(MeshVertex, Normals));
	}

	if(textures.size() != 0) {
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (GLvoid*)offsetof(MeshVertex, TexCoords));
	}

	glBindVertexArray(0);
}

void Mesh::drawWithoutIndices(Shader shad) {
	GLint diffuseNr = 0;
	GLint specularNr = 0;
	for(GLuint i = 0; i < this->textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);

		std::string name = this->textures[i].type;
		std::string number = (name == "texture_diffuse") ? std::to_string(++diffuseNr) : std::to_string(++specularNr);
		glUniform1i(glGetUniformLocation(shad.programID, ("material." + name + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
		printOglErrors(__FILE__, __LINE__);
	}

	glBindVertexArray(VAO);
	printOglErrors(__FILE__, __LINE__);

	glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
	printOglErrors(__FILE__, __LINE__);

	glBindVertexArray(0);
	printOglErrors(__FILE__, __LINE__);

	for(int i = 0; i < this->textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}

void Mesh::drawWithIndices(Shader shad) {
	GLint diffuseNr = 0;
	GLint specularNr = 0;
	for(GLuint i = 0; i < this->textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);

		std::string name = this->textures[i].type;
		std::string number = (name == "texture_diffuse") ? std::to_string(++diffuseNr) : std::to_string(++specularNr);
		glUniform1i(glGetUniformLocation(shad.programID, ("material." + name + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
		printOglErrors(__FILE__, __LINE__);
	}

	//glUniform1f(glGetUniformLocation(shad.programID, "material.shininess"), 16.0f);
	printOglErrors(__FILE__, __LINE__);

	glBindVertexArray(VAO);
	printOglErrors(__FILE__, __LINE__);

	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	printOglErrors(__FILE__, __LINE__);

	glBindVertexArray(0);
	printOglErrors(__FILE__, __LINE__);

	for(int i = 0; i < this->textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

