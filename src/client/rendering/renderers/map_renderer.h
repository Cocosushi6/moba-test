/*
 * map_renderer.h
 *
 *  Created on: Jun 21, 2017
 *      Author: sacha
 */

#ifndef SRC_CLIENT_RENDERING_RENDERERS_MAP_RENDERER_H_
#define SRC_CLIENT_RENDERING_RENDERERS_MAP_RENDERER_H_

#include <iostream>
#include "../../../common/map/world.h"
#include "../renderer.h"
#include "../utils/shader.h"
#include "../assimpModelLoader/mesh.h"
#include "../assimpModelLoader/model.h"

#define GLEW_STATIC
#include <GL/glew.h>

#include <SFML/OpenGL.hpp>

int printOglErrors(char* file, int line);

namespace Rendering {
	class TileRenderer;
	class Renderer;

	class MapRenderer {
		public:
			MapRenderer(Renderer *renderer, World::GameMap* map);
			void renderMap();
			Renderer* getRenderer();
		private:
			void setupMap(); //More or less equivalent to setupMesh in Mesh.cpp
			std::vector<TileRenderer> tileRenderers;
			Renderer* renderer;
			World::GameMap* map;
			Shader shad;
	};

	class TileRenderer {
		public:
			TileRenderer(MapRenderer *mapRend, World::Tile tile, Shader* shad);
			TileRenderer(const TileRenderer& other);
			~TileRenderer();
			void render();
		private:
			MapRenderer *mapRend;
			Texture diffuseTex;
			MeshVertex vertices[4];
			GLuint VBO = 0, VAO = 0, EBO = 0;
			Shader *shad = 0;
	};
}



#endif /* SRC_CLIENT_RENDERING_RENDERERS_MAP_RENDERER_H_ */
