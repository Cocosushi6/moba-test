#ifndef SRC_CAMERA_H_
#define SRC_CAMERA_H_

//include glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//include GL libs
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include "../../common/objects/entities/entity.h"
#include "../../common/consts.h"
#include "../game.h"

enum CameraMovement {
	FORWARD,
	BACK,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Camera {
public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat fov = 45.0f, GLfloat yaw = 0.0f, GLfloat pitch = 0.0f);
	void processKeyboard(CameraMovement movement, GLfloat delta);
	void processMouse(GLfloat xpos, GLfloat ypos);
	void processScroll(GLfloat yoffset);
	glm::mat4 getViewMatrix();
	glm::vec3 getPosition();
	glm::vec3 getFront();
	void toggleLock(glm::vec3 position);
	void focusOn(Objects::Entities::Entity *ent);
	GLfloat getFov();
	bool isLocked() {
		return lock;
	}
	void udpate();
private:
	void update_vectors();
	void checkBounds();

	glm::mat4 view;

	GLfloat pitch = 0.0f;
	GLfloat yaw = 0.0f;

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f); //Camera position at the beginning (that we multiply by cameraFront to move)
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);//vector we add or substract to camera pos (makes going forward (i.e front))
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //Up vector, relative to camera

	GLfloat lastX = 400;
	GLfloat lastY = 400;

	GLfloat fov = 45.0f;
	GLfloat speed = 3.0f;

	bool firstMouse = true;
	bool lock = false;
	bool isFocused = false;

	Objects::Entities::Entity *focusEnt;
};



#endif /* SRC_CAMERA_H_ */
