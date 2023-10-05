#pragma once

#include "Scene.h"
#include "Shader.h"

class MyScene : public Scene
{
public:
	MyScene(GLFWwindow* window, std::shared_ptr<InputHandler> H);
	~MyScene() {};
	void update(float dt);

private:
	unsigned int VBO, VAO;		//POS			//RGB
	float vertexData[24] = { 0.5,0.5,0.0, 1.0,0.2,1.0,
							-0.5,0.5,0.0, 0.0,0.8,0.1,
							-0.5,-0.5,0.0, 0.1,0.6,1.0};
	void makeVAO();
	void render();

	std::shared_ptr<Shader> m_myShader;
};
