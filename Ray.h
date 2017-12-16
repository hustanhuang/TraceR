#pragma once

#include <glm/glm.hpp>

class Ray
{
public:
	Ray() = default;

	Ray(const glm::vec3& a, const glm::vec3& b) : A(a), B(b)
	{
	}

	glm::vec3 origin() const { return A; }
	glm::vec3 direction() const { return B; }
	glm::vec3 point_at_distance(float t) const { return origin() + t * direction(); }

private:
	glm::vec3 A;
	glm::vec3 B;
};
