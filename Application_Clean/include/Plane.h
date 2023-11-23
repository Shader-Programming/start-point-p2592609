#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "glm/common.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <memory>
#include "Shader.h"
#include "Shape.h"

class Plane : public Shape
{
public:
	Plane(unsigned int diffTexture, unsigned int specTexture,  unsigned int normalTexture, float shine);
	~Plane() {};

	void setMaterialValues(std::shared_ptr<Shader> shader) override;

	unsigned int getIndicesCount() { return indices.size(); }
	unsigned int getVAO() { return VAO; }

private:
	unsigned int VAO, EBO, VBO;

	float m_shine;
	unsigned int m_diffuseMap;
	unsigned int m_specularMap;
	unsigned int m_normalMap;

	void makeVAO() override;

	const float floorLevel = -2.0f; 
	const float floorSize = 7.0f;

	std::vector<float> vertexData = {
	-floorSize, floorLevel,  -floorSize,     0.0, 1.0, 0.0, 0.0,0.0,1.0f, 0.0f, 0.0f,
	 floorSize, floorLevel,  -floorSize,     0.0, 1.0, 0.0, 1.0,0.0,1.0f, 0.0f, 0.0f,
	 floorSize, floorLevel,   floorSize,     0.0, 1.0, 0.0, 1.0,1.0,1.0f, 0.0f, 0.0f,
	-floorSize, floorLevel,   floorSize,     0.0, 1.0, 0.0, 0.0,1.0,1.0f, 0.0f, 0.0f
	};
	std::vector<unsigned int> indices = {
		3,2,1,
		3,1,0
	};
};