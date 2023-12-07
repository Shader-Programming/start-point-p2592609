#include "MyScene.h"

MyScene::MyScene(GLFWwindow* window, std::shared_ptr<InputHandler> H) : Scene(window, H)
{
	m_handler = H;
	m_camera = std::make_shared<FirstPersonCamera>();
	
	unsigned int cubeDiff = TextureManager::loadTexture("..\\Resources\\diffuseCube.jpg");
	unsigned int cubeSpec = TextureManager::loadTexture("..\\Resources\\specularCube.jpg");
	unsigned int cubeNorm = TextureManager::loadTexture("..\\Resources\\normalCube.jpg");

	unsigned int floorDiff = TextureManager::loadTexture("..\\Resources\\diffuseFloor.jpg");
	unsigned int floorSpec = TextureManager::loadTexture("..\\Resources\\specularFloor.jpg");
	unsigned int floorNorm = TextureManager::loadTexture("..\\Resources\\normalFloor.jpg");

	m_myShader = std::make_shared<Shader>("..\\Shaders\\VertexShader.glsl", "..\\Shaders\\FragmentShader.glsl");
	m_ppShader = std::make_shared<Shader>("..\\Shaders\\PostProcessingVertexShader.glsl", "..\\Shaders\\PostProcessingFragmentShader.glsl");

	m_directionalLight = std::make_shared<DirectionalLight>(glm::vec3(1.0), glm::vec3(0.0f, -1.0f, 0.0f));
	m_cube = std::make_shared<Cube>(cubeDiff, cubeSpec, cubeNorm, 16);
	m_plane = std::make_shared<Plane>(floorDiff, floorSpec, floorNorm, 16);
	m_pointLight = std::make_shared<PointLight>(glm::vec3(1.0, 1.0, 1.0), glm::vec3(-2.0, 0.0, 0.0), glm::vec3(1.0, 0.22, 0.02));
	m_spotLight = std::make_shared<SpotLight>(glm::vec3(0.5, 1.0, 0.0),glm::vec3(0.0, 7.0, 0.0), glm::vec3(1.0, 0.027, 0.0028), glm::vec3(0.0, -1.0, 0.0), glm::vec2(glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f))));

	m_directionalLight->setLightUniforms(m_myShader);
	m_pointLight->setLightUniforms(m_myShader);
	m_spotLight->setLightUniforms(m_myShader);

	m_postFBO = std::make_shared<FrameBuffer>(1, true);

	m_postProcessing = std::make_shared<FBOquad>();

	setHandler(true);
}

void MyScene::render()
{
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_EQUAL);

	m_postFBO->bind();
	m_postFBO->clearColour();


	m_myShader->use();

	//set uniforms
	m_myShader->setMat4("View", m_view = m_camera->getViewMatrix());
	m_myShader->setMat4("Projection", m_projection = m_camera->getProjectionMatrix());
	m_myShader->setVec3("viewPos", m_camera->getPosition());
	m_myShader->setInt("useNM", useNM);

	glBindVertexArray(m_cube->getVAO());
	m_cube->setTransform(m_myShader);
	m_cube->setMaterialValues(m_myShader);
	glDrawElements(GL_TRIANGLES, m_cube->getIndicesCount(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(m_plane->getVAO());
	m_plane->setTransform(m_myShader);
	m_plane->setMaterialValues(m_myShader);
	glDrawElements(GL_TRIANGLES, m_plane->getIndicesCount(), GL_UNSIGNED_INT, 0); 


	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);

	m_postFBO->bindDefault();
	m_postProcessing->drawColAttachment(m_postFBO->getColourAttachment());
	m_postProcessing->drawDepthAttachment(m_postFBO->getDepthAttachment());


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
		if (m_handler->isKeyPressed(GLFW_KEY_F))
		{
			useNM = !useNM;
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



