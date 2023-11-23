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
	Shape() {}
	~Shape() {};
	virtual void setMaterialValues(std::shared_ptr<Shader> shader) = 0;

	void resetTransform() { m_transform = glm::mat4(1.0); }
	glm::mat4& getModelMatrix() { return m_transform; }
	void setTransform(std::shared_ptr<Shader> shader) { shader->setMat4("Model", m_transform); }

protected:
	virtual void makeVAO() = 0;




	float m_specularStrength;
	glm::vec3 m_colour;
	glm::mat4 m_transform;



};