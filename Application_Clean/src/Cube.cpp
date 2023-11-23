#include "Cube.h"

Cube::Cube(unsigned int diffTexture, unsigned int specTexture, unsigned int normalTexture, float shine) : m_diffuseMap(diffTexture), m_specularMap(specTexture), m_normalMap(normalTexture), m_shine(shine)
{
	makeVAO();
	resetTransform();
}

Cube::~Cube()
{
}

void Cube::setMaterialValues(std::shared_ptr<Shader> shader)
{

	//shader->setVec3("objectColour", m_colour);
	shader->setFloat("shine", m_shine);
	//shader->setFloat("specStrength", m_specularStrength);
	shader->setInt("diffuseMap", 0);
	shader->setInt("specularMap", 1);
	shader->setInt("normalMap", 2);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_diffuseMap);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_specularMap);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_normalMap);
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);
}

