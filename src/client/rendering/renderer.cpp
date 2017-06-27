#include <iostream>
#include <string>

#include "renderer.h"
#include "ui/ui_manager.h"
#include "ui/ui_components.h"
#include "utils/utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

using namespace Rendering;
using namespace std;

Renderer::Renderer(sf::Window* window, Game* game) : window(window), game(game) {
	mapRenderer = new MapRenderer(this, game->getMap());
	uiManager = new UI::UIManager(this);
	cam = new Camera();

}

Renderer::~Renderer() {


	delete mapRenderer;
	delete uiManager;
}

int Renderer::loadShader(string identifier, string vertPath, string fragPath) {
	for(std::map<string, Shader*>::iterator it = shaders.begin(); it != shaders.end(); it++) {
		if(it->first == identifier) {
			cout << "Error while loading new shader : identifier already exists ! Aborting. " << endl;
			return -1;
		}
	}

	Shader *shad = new Shader(vertPath.c_str(), fragPath.c_str());
	if(shad->load() != 0) {
		cout << "Error while loading new shader : shader creation failed ! " << endl;
		return -2;
	}
	shaders[identifier] = shad;
	return 0;
}

void Renderer::render() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	printOglErrors(__FILE__, __LINE__);

	mapRenderer->renderMap();
	printOglErrors(__FILE__, __LINE__);
	renderObjects();
	printOglErrors(__FILE__, __LINE__);

	this->uiManager->renderUI();

	printOglErrors(__FILE__, __LINE__);

	this->window->display();
}

void Renderer::renderObjects() {

}

Camera* Renderer::getCamera() {
	return this->cam;
}

glm::mat4 Renderer::getProjectionMatrix() {
	float aspect = (float)window->getSize().x/(float)window->getSize().y;
	glm::mat4 ret = glm::perspective(glm::radians(cam->getFov()), aspect, 1.0f, 100.0f);
	return ret;
}
