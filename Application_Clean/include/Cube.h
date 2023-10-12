#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "glm/common.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <memory>
#include "Shader.h"
#include "InputHandler.h"

class Cube
{
public:
	Cube();
	~Cube();

	void update(float dt);
	void attachHandler(std::shared_ptr<InputHandler> H);

	void resetTransform() { m_transform = glm::mat4(1.0); }

	unsigned int getVAO() { return VAO; }
	glm::mat4& getModelMatrix() { return m_transform;  }
	unsigned int getIndicesCount() { return cubeIndices.size(); }

	void rotate(float angle, glm::vec3 axis);
	void scale(glm::vec3 axis);
	void translate(glm::vec3 translation);

private:
	void makeVAO();

	unsigned int VAO, VBO, EBO;
	glm::mat4 m_transform;

	std::vector<float> vertexData = {
		//  xyz
		// back
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
		// front
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		// left
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
		// right
		 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.5f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		 // bottom
		 -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		  0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		  0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
		 -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		 // top
		 -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		  0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		  0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
		 -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
	};
	std::vector<unsigned int> cubeIndices = {
		0, 1, 2, 2, 3, 0,
		4, 5, 6, 6, 7, 4,
		8, 9, 10, 10, 11, 8,
		12, 13, 14, 14, 15, 12,
		16, 17, 18, 18, 19, 16,
		20, 21, 22, 22, 23, 20
	};

	std::shared_ptr<InputHandler> m_handler;
};


