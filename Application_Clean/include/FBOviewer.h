#pragma once

#include "Shader.h"
#include <memory>

class FBOviewer
{
public:

	FBOviewer();
	~FBOviewer() {}
	void drawColAttachment(unsigned int textID);
	void drawDepthAttachment(unsigned int texID);

private:
	unsigned int VAO;
	void createQuadVAO();

	std::shared_ptr<Shader> m_colShader;
	std::shared_ptr<Shader> m_depthShader;

	float quadVertices[20] = {
		// positions        // texture Coords
		 -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		  1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,


		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,

	};

	unsigned int quadIndices[6] = {
			3,2,1,
			3,1,0
	};
};