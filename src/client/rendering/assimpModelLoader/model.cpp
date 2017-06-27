#include <iostream>
// Include GLEW
#include <GL/glew.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SOIL/SOIL.h>

//include assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <string>
#include <map>

#include "../utils/shader.h"
#include "model.h"
#include "mesh.h"
#include "../utils/utils.h"

using namespace std;

Model::Model() {}

Model::Model(map<int, Mesh> meshes, map<int, Texture> textures, glm::vec3 position) {
	this->mPosition = position;
	this->loadModel(meshes, textures);
}

Model::Model(std::string path, glm::vec3 position) {
		this->loadModel(path);
		this->mPosition = position;
}

void Model::draw(Shader shad) {
	for(int i = 0; i < this->meshes.size(); i++)
		this->meshes[i].drawWithIndices(shad);
}

void Model::loadModel(std::string path) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if(!scene || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || !scene->mRootNode) {
		std::cout << "ERROR::ASSIMP" << importer.GetErrorString() << std::endl;
		return;
	}
	this->directory = path.substr(0, path.find_last_of('/'));
	this->processNode(scene->mRootNode, scene);
}

//TODO complete this method
//int in meshes map is the index of the texture to be used in the textures vectors
void Model::loadModel(std::map<int, Mesh> meshes, std::map<int, Texture> textures) {
	for(map<int, Mesh>::iterator it = meshes.begin(); it != meshes.end(); it++) {
		vector<Texture> meshTextures; //textures that belong to the mesh with id meshID
		int meshID = it->first;
		for(map<int, Texture>::iterator it = textures.begin(); it != textures.end(); it++) {

		}
	}
}


void Model::processNode(aiNode* node, const aiScene* scene) {
	for(int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->meshes.push_back(this->processMesh(mesh, scene));
	}
	for(int i = 0; i < node->mNumChildren; i++) {
		this->processNode(node->mChildren[i], scene);
	}
}

//Extract all data(vertices, indices, textures) from aiMesh and return Mesh object (which has a renderer)
Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
	std::vector<MeshVertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	for(int i = 0; i < mesh->mNumVertices; i++) {
		MeshVertex vertex;

		//add vertices
		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		//add normals
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normals = vector;

		//If any texture
		if(mesh->mTextureCoords[0]) {
			glm::vec2 texCoords;
			texCoords.x = mesh->mTextureCoords[0][i].x;
			texCoords.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = texCoords;
		} else vertex.TexCoords = glm::vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}

	//TODO add boolean in mesh.cpp to allow rendering without indices
	//add indices
	for(GLuint i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for(int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	//process textures here
	if(mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuseMaps = this->loadMaterialTexture(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<Texture> specularMaps = this->loadMaterialTexture(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTexture(aiMaterial* mat, aiTextureType type, std::string typeName) {
	std::vector<Texture> textures;
	for(int i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;
		mat->GetTexture(type, i, &str);
		std::string texPath(str.data);
		GLboolean skip = false;
		for(int j = 0; j < loadedTextures.size(); j++) {
			if(loadedTextures[j].path == texPath) {
				textures.push_back(loadedTextures[j]);
				skip = true;
				break;
			}
		}
		if(!skip) {
			Texture texture;
			GLint id = TextureFromFile(str.C_Str(), directory);
			if(id != -1) {
				texture.id = id;
			} else {
				break;
			}
			texture.type = typeName;
			texture.path = texPath;
			textures.push_back(texture);
		}
	}
	return textures;
}

GLint Model::TextureFromFile(const char *path, std::string directory) {
	int width, height;
	std::string strPath(path);
	std::string finalPath = directory + "/" + strPath;

	GLuint texture;
	glGenTextures(1, &texture);
	printOglErrors(__FILE__, __LINE__);

	unsigned char* image = SOIL_load_image(finalPath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	if(!image) {
		std::cout << "unable to load image, size : " << sizeof(*image) << std::endl;
		return -1;

	}
	printOglErrors(__FILE__, __LINE__);

	glBindTexture(GL_TEXTURE_2D, texture);
	printOglErrors(__FILE__, __LINE__);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	printOglErrors(__FILE__, __LINE__);
	glGenerateMipmap(GL_TEXTURE_2D);
	printOglErrors(__FILE__, __LINE__);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);
	printOglErrors(__FILE__, __LINE__);

	return texture;
}
