#include "Random.h"

glm::vec3 Random::Vec3(glm::vec3 lower, glm::vec3 upper)
{
	std::random_device rd;
	std::mt19937 gen(rd()); //rd()

	std::uniform_real_distribution<float> distribX(lower.x, upper.x);
	std::uniform_real_distribution<float> distribY(lower.y, upper.y);
	std::uniform_real_distribution<float> distribZ(lower.z, upper.z);
	glm::vec3 randVec = glm::vec3(distribX(gen), distribY(gen), distribZ(gen));

	return randVec;
}

float Random::Float(float lower, float upper)
{
	std::random_device rd;
	std::mt19937 gen(rd()); //rd()
	std::uniform_real_distribution<float> distrib(lower, upper);
	return distrib(gen);
}
