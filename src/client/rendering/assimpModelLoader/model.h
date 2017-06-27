#ifndef SRC_MODEL_H
#define SRC_MODEL_H
#include <iostream>
// Include GLEW

#define GLEW_STATIC
#include <GL/glew.h>

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
#include <map>

#include "../utils/shader.h"
#include "mesh.h"

class Model {
public:
	Model();
	Model(std::map<int, Mesh> vertices, std::map<int, Texture> textures, glm::vec3 position);
	Model(std::string path, glm::vec3 position);
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
	void loadModel(std::map<int, Mesh> meshes, std::map<int, Texture> texture);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	Mesh processMesh(Mesh mesh, std::vector<Texture> textures);
	std::vector<Texture> loadMaterialTexture(aiMaterial* mat, aiTextureType type, std::string typeName);
};

#endif
