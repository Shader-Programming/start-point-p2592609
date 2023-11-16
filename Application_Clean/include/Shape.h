#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "glm/common.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <memory>
#include "Shader.h"

class Shape
{
public:
	Shape(unsigned int diffTexture, unsigned int specTexture, unsigned int normalTexture, float shine) : diffuseMap(diffTexture), specularMap(specTexture), normalMap(normalTexture), m_shine(shine) {}
	~Shape() {};
	virtual void setMaterialValues(std::shared_ptr<Shader> shader);

	void resetTransform() { m_transform = glm::mat4(1.0); }
	glm::mat4& getModelMatrix() { return m_transform; }
	void setTransform(std::shared_ptr<Shader> shader) { shader->setMat4("Model", m_transform); }

	unsigned int getVAO() { return VAO; }

protected:
	void makeVAO(std::vector<float> vertexData, std::vector<unsigned int> indices);

	unsigned int VAO, EBO, VBO;

	float m_shine;
	float m_specularStrength;
	glm::vec3 m_colour;
	glm::mat4 m_transform;

	unsigned int diffuseMap;
	unsigned int specularMap;
	unsigned int normalMap;

};