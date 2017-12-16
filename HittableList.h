#pragma once

#include "Hittable.h"

class HittableList : public Hittable
{
public:
	HittableList(Hittable** l, int n) : list(l), list_size(n)
	{
	}

	bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const override;

	Hittable** list;
	int list_size;
};

bool HittableList::hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const
{
	HitRecord record;
	bool hit_anything = false;
	float closest_so_far = t_max;
	for (int i = 0; i < list_size; i++)
	{
		if (list[i]->hit(r, t_min, closest_so_far, record))
		{
			hit_anything = true;
			closest_so_far = record.t;
			rec = record;
		}
	}
	return hit_anything;
}
