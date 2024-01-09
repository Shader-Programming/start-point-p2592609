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

	m_cube = std::make_shared<Cube>(cubeDiff, cubeSpec, cubeNorm, 16, true);
	m_cube2 = std::make_shared<Cube>(cubeDiff, cubeSpec, cubeNorm, 16, false);
	m_cube2->translate(glm::vec3(1.f, 2.f, 2.f));

	addCubes(cubeDiff, cubeSpec, cubeNorm, 16);

	m_plane = std::make_shared<Plane>(floorDiff, floorSpec, floorNorm, 16);
	m_plane2 = std::make_shared<Plane>(floorDiff, floorSpec, floorNorm, 16);
	m_plane3 = std::make_shared<Plane>(floorDiff, floorSpec, floorNorm, 16);
	

	m_plane2->translate(glm::vec3(8.f, 8.f, 0.f));
	m_plane2->rotate(1.5708f, glm::vec3(0.f, 0.f, 1.f));
	
	m_plane3->translate(glm::vec3(0.f, 8.f, 12.f));
	m_plane3->rotate(1.5708f, glm::vec3(1.f, 0.f, 0.f));

	m_spotLight = std::make_shared<SpotLight>(glm::vec3(1.0, 1.0, 1.0),glm::vec3(0.0, 7.0, 0.0), glm::vec3(1.0, 0.045, 0.0075), glm::vec3(0.0, -1.0, 0.0), glm::vec2(glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f))));

	addPointLights(50);

	m_directionalLight->setLightUniforms(m_myShader);
	m_spotLight->setLightUniforms(m_myShader);

	m_postFBO = std::make_shared<FrameBuffer>(1, true);

	m_postProcessing = std::make_shared<FBOquad>();

	setHandler(true);
}

void MyScene::render()
{

	
	m_postFBO->bind();
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	m_postFBO->clearColour();




	m_myShader->use();

	//set uniforms
	m_myShader->setMat4("View", m_view = m_camera->getViewMatrix());
	m_myShader->setMat4("Projection", m_projection = m_camera->getProjectionMatrix());
	m_myShader->setVec3("viewPos", m_camera->getPosition());
	m_myShader->setInt("useNM", useNM);
	m_myShader->setVec3("slightPosition", m_camera->getPosition());
	m_myShader->setVec3("sDirection", m_camera->getFront());

	glBindVertexArray(m_cube->getVAO());
	m_cube->setTransform(m_myShader);
	m_cube->setMaterialValues(m_myShader);
	glDrawElements(GL_TRIANGLES, m_cube->getIndicesCount(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(m_cube2->getVAO());
	m_cube2->setTransform(m_myShader);
	m_cube2->setMaterialValues(m_myShader);
	glDrawElements(GL_TRIANGLES, m_cube2->getIndicesCount(), GL_UNSIGNED_INT, 0);

	for (int i = 0; i < numCubes; i++)
	{
		glBindVertexArray(m_cubes[i].getVAO());
		m_cubes[i].setTransform(m_myShader);
		m_cubes[i].setMaterialValues(m_myShader);
		glDrawElements(GL_TRIANGLES, m_cubes[i].getIndicesCount(), GL_UNSIGNED_INT, 0);
	}

	glBindVertexArray(m_plane->getVAO());
	m_plane->setTransform(m_myShader);
	m_plane->setMaterialValues(m_myShader);
	glDrawElements(GL_TRIANGLES, m_plane->getIndicesCount(), GL_UNSIGNED_INT, 0); 

	glBindVertexArray(m_plane2->getVAO());
	m_plane2->setTransform(m_myShader);
	m_plane2->setMaterialValues(m_myShader);
	glDrawElements(GL_TRIANGLES, m_plane2->getIndicesCount(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(m_plane3->getVAO());
	m_plane3->setTransform(m_myShader);
	m_plane3->setMaterialValues(m_myShader);
	glDrawElements(GL_TRIANGLES, m_plane3->getIndicesCount(), GL_UNSIGNED_INT, 0);


	glDepthMask(GL_FALSE);
	glDepthFunc(GL_EQUAL);
	
	m_postFBO->bindDefault();
	glDisable(GL_DEPTH_TEST);
	m_postFBO->clearColour();
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	m_postProcessing->drawColAttachment(m_postFBO->getColourAttachment());
	m_postProcessing->drawDepthAttachment(m_postFBO->getDepthAttachment());

	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);


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

	m_cube2->rotate(dt, glm::vec3(0.0f, 1.0f, 0.0f));

	for (int i = 0; i < numCubes; i++)
	{
		m_cubes[i].rotate(dt, Random::Vec3(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
	}
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

void MyScene::addPointLights(int numLights)
{
	
	for (int i = 0; i < numLights; i++)
	{	
		glm::vec3 col = Random::Vec3(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
		glm::vec3 pos = Random::Vec3(glm::vec3(-10.0f, 0.0f, -10.0f), glm::vec3(10.0f, 20.0f, 10.0f));

		m_pointLight.emplace_back(PointLight(col, pos, glm::vec3(1.0, 0.14, 0.07)));
		m_pointLight[i].setLightUniforms(m_myShader, i);
	}
}

void MyScene::addCubes(unsigned int diffTexture, unsigned int specTexture, unsigned int normalTexture, float shine)
{
	for (int i = 0; i < numCubes; i++)
	{
		m_cubes.emplace_back(Cube(diffTexture, specTexture, normalTexture, shine, false));
		m_cubes[i].translate(Random::Vec3(glm::vec3(-5.0f, 0.0f, -5.0f), glm::vec3(5.0f, 10.0f, 5.0f)));
	}
}



