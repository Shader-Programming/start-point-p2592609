#include "PostProcessing.h"

PostProcessing::PostProcessing(unsigned int texture) : m_texture(texture)
{
	makeVAO();
}

void PostProcessing::setMaterialValues(std::shared_ptr<Shader> shader)
{
	shader->setInt("defaultTexture", 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);

}

void PostProcessing::makeVAO()
{
	//create buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	//bind buffers
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);
	//transfer data to GPU
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

}
