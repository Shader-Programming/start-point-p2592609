#pragma once

#include "Scene.h"
#include "Shader.h"
#include "Cube.h"

class MyScene : public Scene
{
public:
	MyScene(GLFWwindow* window, std::shared_ptr<InputHandler> H);
	~MyScene() {};
	void update(float dt);

private:

	void render();

	std::shared_ptr<Cube> m_cube;

	std::shared_ptr<Shader> m_myShader;

	glm::mat4 m_view, m_projection;

};
