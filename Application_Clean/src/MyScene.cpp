#include "MyScene.h"

MyScene::MyScene(GLFWwindow* window, std::shared_ptr<InputHandler> H) : Scene(window, H)
{
	m_handler = H;
	m_camera = std::make_shared<FirstPersonCamera>();
	m_camera->attachHandler(m_window, m_handler);

	makeVAO();

	m_myShader = std::make_shared<Shader>("..\\Shaders\\VertexShader.glsl", "..\\Shaders\\FragmentShader.glsl");
}

void MyScene::makeVAO()
{
	//create buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	//bind buffers
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * cubeIndices.size(), cubeIndices.data(), GL_STATIC_DRAW);
	//transfer data to GPU
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexData.size(), vertexData.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);


}

void MyScene::render()
{
	m_model = glm::mat4(1.0f);

	m_projection = m_camera->getProjectionMatrix();
	m_view = m_camera->getViewMatrix();
	m_myShader->use();
	//set uniforms
	m_myShader->setMat4("View", m_view);
	m_myShader->setMat4("Projection", m_projection);
	m_myShader->setMat4("Model", m_model);


	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, cubeIndices.size(), GL_UNSIGNED_INT, 0);
}

void MyScene::update(float dt)
{
	m_camera->update(dt);
	render();
}

