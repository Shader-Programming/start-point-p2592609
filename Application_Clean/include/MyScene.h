#pragma once

#include "Scene.h"
#include "Shader.h"
#include "Cube.h"
#include "Plane.h"
#include "Lights/DirectionalLight.h"
#include "Lights/PointLight.h"
#include "Lights/SpotLight.h"
#include "Textures/TextureManager.h"
#include "FBOquad.h"
#include "FrameBuffer.h"
#include <vector>
#include "Random.h"

class MyScene : public Scene
{
public:
	MyScene(GLFWwindow* window, std::shared_ptr<InputHandler> H);
	~MyScene() {};
	void update(float dt);
	void setHandler(bool handler);
	void addPointLights(int numLights);
	void addCubes(unsigned int diffTexture, unsigned int specTexture, unsigned int normalTexture, float shine);

private:

	void render();

	std::shared_ptr<Cube> m_cube;
	std::shared_ptr<Cube> m_cube2;

	std::vector<Cube> m_cubes;
	
	std::shared_ptr<Plane> m_plane;
	std::shared_ptr<Plane> m_plane2;
	std::shared_ptr<Plane> m_plane3;

	std::shared_ptr<Shader> m_myShader;
	std::shared_ptr<Shader> m_ppShader;
	std::shared_ptr<FBOquad> m_postProcessing;
	std::shared_ptr<FrameBuffer> m_postFBO;
	std::shared_ptr<DirectionalLight> m_directionalLight;
	std::vector<PointLight> m_pointLight;
	std::shared_ptr<SpotLight> m_spotLight;
	glm::mat4 m_view, m_projection;

	Random ranGen;

	int numCubes = 10;
	unsigned int m_ID;
	unsigned int textureColour;

	bool ab;
	bool useNM = false;

};
