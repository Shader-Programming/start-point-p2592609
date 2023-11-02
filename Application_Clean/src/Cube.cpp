#include "Cube.h"

Cube::Cube(glm::vec3 col, float shine, float specStrength) : Shape(col, shine, specStrength)
{
	makeVAO();
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

void Cube::makeVAO()
{
	//create buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	//bind buffers
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);
	//transfer data to GPU
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexData.size(), vertexData.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}
