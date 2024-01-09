#pragma once
#include <random>
#include "glm/common.hpp"

class Random
{
public:
	static glm::vec3 Vec3(glm::vec3 lower, glm::vec3 upper);
	static float Float(float lower, float upper);



};
