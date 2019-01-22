#include <stdio.h>
#define M_PI 3.141592653f
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#undef STB_IMAGE_WRITE_IMPLEMENTATION

#include "vec3.h"
#include "image.h"
#include "ray.h"

typedef struct {
	float r, g, b;
} Material;

Material material_new(float r, float g, float b) {
	Material m;
	m.r = r;
	m.g = g;
	m.b = b;
	return m;
}

typedef struct {
	vec3 p;
	float r;
	Material mat;
} Sphere;

Sphere sphere_new(vec3 p, float r) {
	Sphere s;
	s.p = p;
	s.r = r;

	s.mat = material_new(255, 115, 58);
	return s;
}

int main(int argc, char *argv[]) {
	Image img = image_new(800, 600);
	image_fill(&img, 215, 211, 255);
	float fov = M_PI * 0.5f;
	Sphere s = sphere_new(vec3_new(10.0f, -15.0f, 40.0f), 15.0f);
	for (int y = 0; y < img.height; ++y) {
		for (int x = 0; x < img.width; ++x) {
			float xx =  (2.0f * (x + 0.5f) / (float)img.width - 1.0f) * tan(fov * 0.5f) * (float)img.width / (float)img.height;
			float yy = -(2.0f * (y + 0.5f) / (float)img.height - 1.0f) * tan(fov * 0.5f);
			
			Ray ray = ray_new(
				vec3_new(0.0f, 0.0f, 0.0f),
				vec3_new(
					xx,
					yy,
					1.0f
				)
			);
			
			RayHit hits[2];
			int r = ray_intersects_sphere(&ray, s.p, s.r, hits);
			if (r > 0) {
				vec3 up = vec3_new(0.0f, 1.0f, 0.0f);
				float light = vec3_dot(hits[0].n, up);
				if (light > 1.0f) light = 1.0f;
				else if (light < 0.0f) light = 0.0f;
				image_set(&img, x, y, 0, (int)(255.0f * light), 0);
			}
		}
	}
	
	image_save(&img, "out.png");
	image_destroy(&img);

	return 0;
}
