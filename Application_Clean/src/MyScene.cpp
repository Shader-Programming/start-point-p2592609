#include "MyScene.h"

MyScene::MyScene(GLFWwindow* window, std::shared_ptr<InputHandler> H) : Scene(window, H)
{
	m_handler = H;
	m_camera = std::make_shared<FirstPersonCamera>();
	
	m_myShader = std::make_shared<Shader>("..\\Shaders\\VertexShader.glsl", "..\\Shaders\\FragmentShader.glsl");
	m_dierectionalLight = std::make_shared<DirectionalLight>(glm::vec3(1.0), glm::vec3(0.0f, -1.0f, 0.0f));
	m_cube = std::make_shared<Cube>(glm::vec3(0.1, 0.2, 0.3), 16, 2);

	m_dierectionalLight->setLightUniforms(m_myShader);
	m_cube->setCubeMaterialValues(m_myShader);

	setHandler(true);
}

void MyScene::render()
{
	//m_cube->getModelMatrix() = glm::mat4(1.0f);
	
	m_myShader->use();

	//set uniforms
	m_myShader->setMat4("View", m_view = m_camera->getViewMatrix());
	m_myShader->setMat4("Projection", m_projection = m_camera->getProjectionMatrix());
	m_myShader->setVec3("viewPos", m_camera->getPosition());

	glBindVertexArray(m_cube->getVAO());
	m_cube->setTransform(m_myShader);
	glDrawElements(GL_TRIANGLES, m_cube->getIndicesCount(), GL_UNSIGNED_INT, 0);

	//New Cube
	/*m_cube->rotate((float)(glfwGetTime() * 0.5), glm::vec3(0.0, 1.0, 0.0));
	//m_cube->translate(glm::vec3(5.0, 0.0, 0.0));
	
	m_cube->scale(glm::vec3(0.5, 0.5, 0.5));

	m_myShader->setMat4("Model", m_cube->getModelMatrix());

	glDrawElements(GL_TRIANGLES, m_cube->getIndicesCount(), GL_UNSIGNED_INT, 0);*/
}

void MyScene::update(float dt)
{
	if (m_handler->keyHasBeenPressed()) {
		if (m_handler->isKeyPressed(GLFW_KEY_T)) {
			if (ab)
			{
				setHandler(false);
			}
			else
			{
				setHandler(true);
			}
			
		}
	} 

	if (ab)
	{
		m_camera->update(dt);
	}
	else
	{
		m_cube->update(dt);
	}
	
	render();
	
}

void MyScene::setHandler(bool handler)
{
	if (handler)
	{
		m_cube->attachHandler(nullptr);
		m_camera->attachHandler(m_window, m_handler);
		ab = true;
	}
	else
	{
		m_camera->attachHandler(m_window, nullptr);
		m_cube->attachHandler(m_handler);
		ab = false;
	}
}



