#include <iostream>
#include <string>

#include "renderer.h"
#include "ui/ui_manager.h"
#include "ui/ui_components.h"
#include "utils/utils.h"

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

//OpenGL headers TODO
Rendering::Renderer::Renderer(sf::RenderWindow *window, Game *game)
	: window(window), game(game), map("map.obj", glm::vec3(0.0, 0.0, 0.0)) {

	this->uiManager = new UI::UIManager(this);
	Shader shad("shaders/map_shader.vert", "shaders/map_shader.frag");
	shaders["map_shader"] = &shad;
	this->init();
}

Rendering::Renderer::~Renderer() {
	delete uiManager;
}

void Rendering::Renderer::init() {
	//Setup map data
	World::GameMap* map = game->getMap();
	for(std::vector<World::Tile> line : map->getMapGrid()->getTiles()) {
		for(World::Tile t : line) {
			std::vector<MeshVertex> vertices;
			for(int i = 0; i < 4; i++) {
				MeshVertex vert;
				vert.Position = t.getCoordinates().vertices[i].coordinates;
				vert.Normals = t.getCoordinates().vertices[i].normals;
				vert.TexCoords = t.getCoordinates().vertices[i].textCoords;
				vertices.push_back(vert);
				i++;
			}
			Mesh tile(vertices);

		}
	}


	//End setup map data
}

void Rendering::Renderer::renderMap() {


	printOglErrors(__FILE__, __LINE__);
}

void Rendering::Renderer::addEntityModel(int id, Model *model) {
        entityModels[id] = model;
}

void Rendering::Renderer::drawLoadingScreen(std::string message) {
	sf::Font font;
	if(!font.loadFromFile("DejaVuSans.ttf")) {
		std::cout << "Couldn't load basic font DejaVuSans.ttf. Things will soon get ugly around here. " << std::endl;
		return;
	}

	sf::Text text;
	text.setFont(font);
	text.setString(message);
	text.setCharacterSize(20);
	text.setColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);
	this->window->draw(text);
	this->window->display();
}

//method to be called in while loop
void Rendering::Renderer::render() {
	glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//Do OGL rendering here
	this->renderMap();

	this->window->pushGLStates();

	this->uiManager->renderUI();

	this->window->popGLStates();

	this->window->display();
}
