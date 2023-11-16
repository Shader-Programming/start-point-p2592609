#include "Plane.h"

Plane::Plane(unsigned int diffTexture, unsigned int specTexture, unsigned int normalTexture, float shine) : Shape(diffTexture, normalTexture, specTexture, shine)
{
	makeVAO(vertexData, indices);
	resetTransform();
}



