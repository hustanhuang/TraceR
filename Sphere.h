#pragma once

#include "Hittable.h"
#include "Random.h"

class Sphere : public Hittable
{
public:
	Sphere(glm::vec3 cen, float r) : center(cen), radius(r)
	{
	};

	bool hit(const Ray& r, float t_min, float r_max, HitRecord& rec) const override;

	glm::vec3 center;
	float radius;
};

bool Sphere::hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const
{
	float fuzz_radius = radius + radius / 524288 * rand01();

	glm::vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - fuzz_radius * fuzz_radius;

	float discriminant = b * b - a * c;

	if (discriminant > 0)
	{
		float x = (-b - sqrt(b * b - a * c)) / a;
		if (x < t_max && x > t_min)
		{
			rec.t = x;
			rec.p = r.point_at_distance(rec.t);
			rec.normal = (rec.p - center) / fuzz_radius;
			return true;
		}
		x = (-b + sqrt(b * b - a * c)) / a;
		if (x < t_max && x > t_min)
		{
			rec.t = x;
			rec.p = r.point_at_distance(rec.t);
			rec.normal = (rec.p - center) / fuzz_radius;
			return true;
		}
	}
	return false;
}
