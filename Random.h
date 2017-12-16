#pragma once

#include <random>
#include <chrono>
#include "glm/glm.hpp"

#define M_PI 3.14159265358979323846f

float rand01()
{
	static uint64_t time_seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	static std::seed_seq ss{uint32_t(time_seed & 0xFFFFFFFF), uint32_t(time_seed >> 32)};
	static std::mt19937_64 rng(ss);
	static std::uniform_real_distribution<float> unif(0, 1);
	return unif(rng);
}

glm::vec3 random_in_unit_sphere()
{
	float phi = rand01() * M_PI;
	float theta = rand01() * 2 * M_PI;
	return glm::vec3(
		sin(theta) * cos(phi),
		sin(theta) * sin(phi),
		cos(theta)
	);
}
