#include "map_renderer.h"

#define GLEW_STATIC
#include <GL/glew.h>

#include "../utils/utils.h"

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>


using namespace std;
using namespace Rendering;

MapRenderer::MapRenderer(Renderer* renderer, World::GameMap* map) : renderer(renderer), map(map), shad("shaders/map_shader.vert", "shaders/map_shader.frag") {
	if(shad.load() != 0) {
		cout << "Shader loading failed !! class : MapRenderer (map_renderer.cpp)" << endl;
	}
	this->setupMap();
}

void MapRenderer::setupMap() {
	int i = 0;
	for(vector<World::Tile> tiles : this->map->getMapGrid()->getTiles()) {
		for(World::Tile tile : tiles) {
			TileRenderer renderer(this, tile, &shad);
			tileRenderers.push_back(renderer);
			i++;
		}
	}
	cout << i << " tile renderers created" << endl;
}


void MapRenderer::renderMap() {
	for(TileRenderer rend : tileRenderers) {
		rend.render();
	}
}

Renderer* MapRenderer::getRenderer() {
	return this->renderer;
}

TileRenderer::TileRenderer(MapRenderer* mapRend, World::Tile tile, Shader* shad) {
	this->mapRend = mapRend;
	this->shad = shad;

	for(int i = 0; i < 4; i++) {
		Vertex currentVertex = tile.getCoordinates().vertices[i];
		vertices[i].Position = glm::vec3(currentVertex.coordinates.x, currentVertex.coordinates.y, currentVertex.coordinates.z);
		vertices[i].Normals = glm::vec3(currentVertex.normals.x, currentVertex.normals.y, currentVertex.normals.z);
		vertices[i].TexCoords = glm::vec2(currentVertex.textCoords.x, currentVertex.textCoords.y);
	}
	unsigned int indices[] = {
			0, 1, 3,
			1, 2, 3
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	printOglErrors(__FILE__, __LINE__);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	printOglErrors(__FILE__, __LINE__);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	printOglErrors(__FILE__, __LINE__);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (GLvoid*)offsetof(MeshVertex, Normals));
	glEnableVertexAttribArray(1);
	printOglErrors(__FILE__, __LINE__);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (GLvoid*)offsetof(MeshVertex, TexCoords));
	glEnableVertexAttribArray(2);
	printOglErrors(__FILE__, __LINE__);

	glBindVertexArray(0);

	diffuseTex.path = "textures" + tile.getTileType() + ".png";
	diffuseTex.type = "diffuse";
	diffuseTex.id = Model::TextureFromFile(string(tile.getTileType() + ".png").c_str(), "textures");

	shad->use();
	int texLocation = glGetUniformLocation(shad->programID, "texture1");
	glUniform1i(texLocation, 0);
	printOglErrors(__FILE__, __LINE__);
}

TileRenderer::TileRenderer(const TileRenderer& other) :
mapRend(other.mapRend), diffuseTex(other.diffuseTex), vertices(other.vertices), VBO(other.VBO), VAO(other.VAO), shad(other.shad) {}

TileRenderer::~TileRenderer() {
}

void TileRenderer::render() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseTex.id);
	printOglErrors(__FILE__, __LINE__);

	shad->use();
	printOglErrors(__FILE__, __LINE__);
	glm::mat4 model;
	glm::mat4 view = mapRend->getRenderer()->getCamera()->getViewMatrix();
    glm::mat4 projection = mapRend->getRenderer()->getProjectionMatrix();
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); //is all zeros because the "local" coordinates are in fact "world" ones (so no need to transform to "world" coordinates)
	printOglErrors(__FILE__, __LINE__);
	int modelLoc = glGetUniformLocation(shad->programID, "model");
	printOglErrors(__FILE__, __LINE__);
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	printOglErrors(__FILE__, __LINE__);

	glUniformMatrix4fv(glGetUniformLocation(shad->programID, "view"), 1, GL_FALSE, glm::value_ptr(view));
	printOglErrors(__FILE__, __LINE__);

	glUniformMatrix4fv(glGetUniformLocation(shad->programID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	printOglErrors(__FILE__, __LINE__);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseTex.id);
	glBindVertexArray(VAO);
	printOglErrors(__FILE__, __LINE__);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	printOglErrors(__FILE__, __LINE__);
	glBindVertexArray(0);
}
