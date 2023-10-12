#include "MyScene.h"

MyScene::MyScene(GLFWwindow* window, std::shared_ptr<InputHandler> H) : Scene(window, H)
{
	m_handler = H;
	m_camera = std::make_shared<FirstPersonCamera>();
	//m_camera->attachHandler(m_window, m_handler);
	

	m_myShader = std::make_shared<Shader>("..\\Shaders\\VertexShader.glsl", "..\\Shaders\\FragmentShader.glsl");
	m_cube = std::make_shared<Cube>();
	m_cube->attachHandler(m_handler);
}

void MyScene::render()
{
	//m_cube->getModelMatrix() = glm::mat4(1.0f);
	m_projection = m_camera->getProjectionMatrix();
	m_view = m_camera->getViewMatrix();
	m_myShader->use();
	//set uniforms
	m_myShader->setMat4("View", m_view);
	m_myShader->setMat4("Projection", m_projection);
	m_myShader->setMat4("Model", m_cube->getModelMatrix());

	glBindVertexArray(m_cube->getVAO());
	glDrawElements(GL_TRIANGLES, m_cube->getIndicesCount(), GL_UNSIGNED_INT, 0);

	//New Cube
	/*m_cube->rotate((float)(glfwGetTime() * 0.5), glm::vec3(0.0, 1.0, 0.0));
	m_cube->translate(glm::vec3(5.0, 0.0, 0.0));
	
	m_cube->scale(glm::vec3(0.5, 0.5, 0.5));

	m_myShader->setMat4("Model", m_cube->getModelMatrix());

	glDrawElements(GL_TRIANGLES, m_cube->getIndicesCount(), GL_UNSIGNED_INT, 0);*/
}

void MyScene::update(float dt)
{
	m_cube->update(dt);
	//m_camera->update(dt);
	render();
	
}

