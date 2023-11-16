#include "Cube.h"

Cube::Cube(unsigned int diffTexture, unsigned int specTexture, unsigned int normalTexture, float shine) : Shape(diffTexture, specTexture, normalTexture, shine)
{
	makeVAO(vertexData, indices);
	resetTransform();
}

Cube::~Cube()
{
}

void Cube::update(float dt)
{
	float vel = 5.0f * dt;

	if (m_handler->keyHasBeenPressed()) {
		if (m_handler->isKeyPressed(GLFW_KEY_W)) {
			translate(glm::vec3(0.0, 0.0, 1.0) * vel);
		}
		if (m_handler->isKeyPressed(GLFW_KEY_S)) {
			translate(glm::vec3(0.0, 0.0, -1.0) * vel);
		}
		if (m_handler->isKeyPressed(GLFW_KEY_A)) {
			translate(glm::vec3(-1.0, 0.0, 0.0) * vel);
		}
		if (m_handler->isKeyPressed(GLFW_KEY_D)) {
			translate(glm::vec3(1.0, 0.0, 0.0)* vel);
		}
	}

	m_handler->endFrame();  // reset delta values

}

void Cube::attachHandler(std::shared_ptr<InputHandler> H)
{
	m_handler = H;
}

void Cube::rotate(float angle, glm::vec3 axis)
{
	m_transform = glm::rotate(m_transform, angle, axis);
}

void Cube::scale(float scaleFactor, glm::vec3 axis)
{
	m_transform = glm::scale(m_transform, axis);
}

void Cube::translate(glm::vec3 translation)
{
	m_transform = glm::translate(m_transform, translation);
}

