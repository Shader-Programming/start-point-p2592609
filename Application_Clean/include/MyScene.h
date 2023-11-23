#pragma once

#include "Scene.h"
#include "Shader.h"
#include "Cube.h"
#include "Plane.h"
#include "Lights/DirectionalLight.h"
#include "Lights/PointLight.h"
#include "Lights/SpotLight.h"
#include "Textures/TextureManager.h"

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
	std::shared_ptr<Plane> m_plane;
	std::shared_ptr<Shader> m_myShader;
	std::shared_ptr<Shader> m_postProcessing;
	std::shared_ptr<DirectionalLight> m_directionalLight;
	std::shared_ptr<PointLight> m_pointLight;
	std::shared_ptr<SpotLight> m_spotLight;
	glm::mat4 m_view, m_projection;

	bool ab;
	bool useNM = false;

};
