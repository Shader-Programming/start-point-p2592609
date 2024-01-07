#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "glm/common.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <memory>
#include "Shader.h"
#include "Shape.h"
#include "InputHandler.h"
#include "Textures/TextureManager.h"

class Cube : public Shape
{
public:
	Cube(unsigned int diffTexture, unsigned int specTexture, unsigned int normalTexture, float shine, bool isPlayer);
	~Cube();

	void setMaterialValues(std::shared_ptr<Shader> shader) override;

	void update(float dt);
	void attachHandler(std::shared_ptr<InputHandler> H);

	unsigned int getIndicesCount() { return indices.size(); }
	unsigned int getVAO() { return VAO; }

	void rotate(float angle, glm::vec3 axis);
	void scale(float scaleFactor, glm::vec3 axis);
	void translate(glm::vec3 translation);

private:
	unsigned int VAO, EBO, VBO;

	float m_shine;
	unsigned int m_diffuseMap;
	unsigned int m_specularMap;
	unsigned int m_normalMap;

	bool player;

	void makeVAO() override;

	std::vector<float> vertexData = {
		//  xyz, normal,uv, tan
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,1.0f, 0.0f, 0.0f,
		// front
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,-1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,-1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,-1.0f, 0.0f, 0.0f,
		// left
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,0.0f, 0.0f, 1.0f,
		// right
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,0.0f, 0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,0.0f, 0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,0.0f, 0.0f, -1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,0.0f, 0.0f, -1.0f,
		 // bottom
		 -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,1.0f, 0.0f, 0.0f,
		  0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,1.0f, 0.0f, 0.0f,
		  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,1.0f, 0.0f, 0.0f,
		 -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,1.0f, 0.0f, 0.0f,
		 // top
		 -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,1.0f, 0.0f, 0.0f,
		  0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,1.0f, 0.0f, 0.0f,
		  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,1.0f, 0.0f, 0.0f,
		 -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,1.0f, 0.0f, 0.0f
	};
	std::vector<unsigned int> indices = {
		0, 1, 2, 2, 3, 0,
		4, 5, 6, 6, 7, 4,
		8, 9, 10, 10, 11, 8,
		12, 13, 14, 14, 15, 12,
		16, 17, 18, 18, 19, 16,
		20, 21, 22, 22, 23, 20
	};

	std::shared_ptr<InputHandler> m_handler;
};


