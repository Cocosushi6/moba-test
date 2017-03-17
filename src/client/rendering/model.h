#ifndef SRC_MODEL_H
#define SRC_MODEL_H
#include <iostream>
// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//include assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <string>

#include "shader.h"
#include "mesh.h"

class Model {
public:
	Model(std::string path, glm::vec3 position) {
		this->loadModel(path);
		this->mPosition = position;
	}
	void draw(Shader shader);
	glm::vec3 getPosition() {
		return this->mPosition;
	}
	void move(float x, float y, float z) {
		glm::vec3 add(x, y, z);
		mPosition += add;
	}
	static GLint TextureFromFile(const char *path, std::string directory);
private:
	std::vector<Mesh> meshes;
	std::vector<Texture> loadedTextures;
	std::string directory;
	glm::vec3 mPosition;
	//methods
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTexture(aiMaterial* mat, aiTextureType type, std::string typeName);
};

#endif
