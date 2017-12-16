#pragma once

#include "Ray.h"

class Camera
{
public:
	Camera(float ratio)
	{
		lower_left_corner = glm::vec3(-ratio, -1.0f, -1.0f);
		horizontal = glm::vec3(2 * ratio, 0.0f, 0.0f);
		vertical = glm::vec3(0.0f, 2.0f, 0.0f);
		origin = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	Ray get_ray(float u, float v)
	{
		return Ray(origin, lower_left_corner + u * horizontal + v * vertical);
	}

	glm::vec3 lower_left_corner;
	glm::vec3 horizontal;
	glm::vec3 vertical;
	glm::vec3 origin;
};
