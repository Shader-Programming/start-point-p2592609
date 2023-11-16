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

	unsigned int getIndicesCount() { return indices.size(); }

private:

	const float floorLevel = -2.0f; 
	const float floorSize = 7.0f;

	std::vector<float> vertexData = {
		-floorSize, floorLevel,  -floorSize,     0.0, 1.0, 0.0, 0.0,0.0,
		floorSize, floorLevel,  -floorSize,     0.0, 1.0, 0.0, 1.0,0.0,
		floorSize, floorLevel,   floorSize,     0.0, 1.0, 0.0, 1.0,1.0,
		-floorSize, floorLevel,   floorSize,     0.0, 1.0, 0.0, 0.0,1.0,
	};
	std::vector<unsigned int> indices = {
		3,2,1,
		3,1,0
	};
};