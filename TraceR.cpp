#include "TraceR.h"

#include <thread>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include "Sphere.h"
#include "HittableList.h"
#include "Random.h"

void TraceR::write_pixel(int x, int y, glm::vec3 c)
{
	const float b256 = 255.99;
	size_t byte_pos = (width * (height - 1 - y) + x) * 3;

	img[byte_pos] = byte(b256 * c.r);
	img[byte_pos + 1] = byte(b256 * c.g);
	img[byte_pos + 2] = byte(b256 * c.b);
}

void TraceR::write_img(const char* fname)
{
	stbi_write_png(fname, width, height, 3, img, width * 3);
}

glm::vec3 TraceR::trace(const Ray& r, int depth)
{
	HitRecord rec;
	if (world->hit(r, 0.0f, INFINITY, rec))
	{
		if (depth > 64)
			return glm::vec3(1, 1, 1);

		glm::vec3 target_dir = rec.normal + random_in_unit_sphere();
		glm::vec3 c = 0.5f * trace(Ray(rec.p, target_dir), depth + 1);

		return c;
	}

	glm::vec3 unit_direction = normalize(r.direction());
	float t = 0.5f * (unit_direction.y + 1.0f);
	return (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.4f, 0.8f, 1.0f);
}

void TraceR::render_line(int y)
{
	if (y < 0 || y >= height)
		return;

	for (int x = 0; x < width; x++)
	{
		glm::vec3 color(0, 0, 0);

		for (int i = 0; i < samples; i++)
		{
			float u = float(x + rand01()) / float(width);
			float v = float(y + rand01()) / float(height);
			Ray ray = cam.get_ray(u, v);
			color += trace(ray, 0);
		}

		color /= samples;

		glm::vec3 gamma_corrected(sqrt(color.r), sqrt(color.g), sqrt(color.b));

		write_pixel(x, y, gamma_corrected);
	}
}

int TraceR::get_line()
{
	std::lock_guard<std::mutex> guard(lines_traced_mutex);
	return lines_traced++;
}

void TraceR::render()
{
	Hittable* hittables[2];
	hittables[0] = new Sphere(glm::vec3(0, 0, -1), 0.5f);
	hittables[1] = new Sphere(glm::vec3(0, -10000.5f, -1), 10000.0f);
	world = new HittableList(hittables, 2);

	typedef std::thread* thread_ptr;
	int thread_num = std::thread::hardware_concurrency();
	thread_ptr* threads = new thread_ptr[thread_num];
	for (int i = 0; i < thread_num; i++)
		threads[i] = new std::thread([this]()
		{
			for (int y = get_line(); 0 <= y && y < height; y = get_line()) {
				printf("tracing line %d\n", y);
				render_line(y);
			}
		});
	for (int i = 0; i < thread_num; i++)
	{
		threads[i]->join();
		delete threads[i];
	}
	delete[] threads;

	delete world;
	delete hittables[0];
	delete hittables[1];

	write_img("output.png");
}
