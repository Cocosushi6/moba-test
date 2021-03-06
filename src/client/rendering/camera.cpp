#include "camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat fov, GLfloat yaw, GLfloat pitch) : cameraPos(position), cameraUp(up), fov(fov), yaw(yaw), pitch(pitch) {
	update_vectors();
}

void Camera::processKeyboard(CameraMovement movement, GLfloat delta) {
	GLfloat velocity = speed * delta;
	switch(movement) {
	case FORWARD :
		cameraPos += velocity * cameraFront;
		break;
	case BACK :
		cameraPos -= velocity * cameraFront;
		break;
	case LEFT :
		cameraPos -= glm::normalize(glm::cross(cameraUp, cameraFront)) * velocity; //cross product of two vector give a third one perpendicular to both of them
		break;
	case RIGHT :
		cameraPos += glm::normalize(glm::cross(cameraUp, cameraFront)) * velocity;
		break;
	case UP :
		cameraPos += cameraUp;
		break;
	case DOWN :
		cameraPos -= cameraUp;
	}
	update_vectors();
}

void Camera::processScroll(GLfloat yoffset) {
	if(fov >= 1.0f && fov < 90.0f)
		fov -= yoffset;
	if(fov < 1.0f)
		fov = 1.0f;
	if(fov > 90.0f)
		fov = 90.0f;
}

void Camera::processMouse(GLfloat xpos, GLfloat ypos) {
	if(firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLdouble xOffset = xpos - lastX;
	GLdouble yOffset = lastY - ypos; //Reverse because mouse coordinates are too.
	lastX = xpos;
	lastY = ypos;

	GLdouble sensitivity = 0.05;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	pitch += yOffset;
	yaw += xOffset;

	if(pitch > 89.0f) {
		pitch = 89.0f;
	} else if(pitch < -89.0f) {
		pitch = -89.0f;
	}
	update_vectors();
}

void Camera::udpate() {
	//follow focused entity if it isn't NULL and camera is told to follow an Entity
}

//updateVectors generates the cameraFront vector (from values of yaw & pitch), which is used when moving.
void Camera::update_vectors() {
	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	this->cameraFront = glm::normalize(front);
}

GLfloat Camera::getFov() {
	return this->fov;
}

glm::vec3 Camera::getFront() {
	return this->cameraFront;
}

glm::vec3 Camera::getPosition() {
	return this->cameraPos;
}

glm::mat4 Camera::getViewMatrix() {
	return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::focusOn(Objects::Entities::Entity *ent) {
	this->isFocused = true;
	this->focusEnt = ent;
}

void Camera::toggleLock(glm::vec3 position) {
	lock = !lock;
	//On lock, get to position
	if(lock) {
		this->cameraPos = position;
	}
}
