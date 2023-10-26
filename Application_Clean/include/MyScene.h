#pragma once

#include "Scene.h"
#include "Shader.h"
#include "Cube.h"
#include "Lights/DirectionalLight.h"
#include "Lights/PointLight.h"

class MyScene : public Scene
{
public:
	MyScene(GLFWwindow* window, std::shared_ptr<InputHandler> H);
	~MyScene() {};
	void update(float dt);
	void setHandler(bool handler);


private:

	void render();

	std::shared_ptr<Cube> m_cube;
	std::shared_ptr<Shader> m_myShader;
	std::shared_ptr<DirectionalLight> m_directionalLight;
	std::shared_ptr<PointLight> m_pointLight;
	glm::mat4 m_view, m_projection;

	bool ab;

};
