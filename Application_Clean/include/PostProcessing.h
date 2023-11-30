#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "glm/common.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <memory>
#include "Shader.h"

class PostProcessing
{
public:
	PostProcessing(unsigned int texture);
	~PostProcessing() {};

	void setMaterialValues(std::shared_ptr<Shader> shader);

	unsigned int getIndicesCount() { return sizeof(quadIndices); }
	unsigned int getVAO() { return VAO; }

private:
	unsigned int VAO, EBO, VBO;

	unsigned int m_texture;

	void makeVAO();

	float quadVertices[20] = {
		// positions        // texture Coords
		 -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		  1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,


		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,

	};

	unsigned int quadIndices[6] = {
			3,2,1,
			3,1,0
	};

};