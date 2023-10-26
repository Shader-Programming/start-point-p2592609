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
	Shape(glm::vec3 col, float shine, float specStrength) : m_colour(col), m_shine(shine), m_specularStrength(specStrength) {}
	~Shape() {};
	virtual void setMaterialValues(std::shared_ptr<Shader> shader) {
		shader->setVec3("objectColour", m_colour);
		shader->setFloat("shine", m_shine);
		shader->setFloat("specStrength", m_specularStrength);
	};

	virtual void resetTransform() { m_transform = glm::mat4(1.0); }
	glm::mat4& getModelMatrix() { return m_transform; }
	void setTransform(std::shared_ptr<Shader> shader) { shader->setMat4("Model", m_transform); }

protected:
	float m_shine;
	float m_specularStrength;
	glm::vec3 m_colour;
	glm::mat4 m_transform;

};