#pragma once

#include <mutex>
#include "glm/glm.hpp"

#include "Camera.h"
#include "Hittable.h"

class TraceR
{
public:
	TraceR(size_t w, size_t h, int s) : width(w), height(h), samples(s), cam(float(w) / float(h))
	{
		size_t img_len = w * h * 3;
		img = new byte[img_len];
		memset(img, 0, img_len);
	}

	~TraceR()
	{
		delete[] img;
	}

	TraceR(const TraceR& other) = delete;
	TraceR& operator=(const TraceR& other) = delete;

	glm::vec3 trace(const Ray& r, int depth);
	void render_line(int y);
	int get_line();
	void render();

private:
	typedef unsigned char byte;

	void write_pixel(int x, int y, glm::vec3 c);
	void write_img(const char* fname);

	size_t width;
	size_t height;
	int samples;
	byte* img;

	Camera cam;

	Hittable* world;

	// log
	int lines_traced;
	std::mutex lines_traced_mutex;
};
