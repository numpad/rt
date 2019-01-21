#include <stdio.h>

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

	Ray ray = ray_new(vec3_new(0.0f, 0.0f, 0.0f), vec3_new(0.0f, 0.0f, 1.0f));
	Sphere s = sphere_new(vec3_new(0.0f, 0.0f, 200.0f), 5.0f);

	vec3 is[2];
	int r = ray_intersects_sphere(&ray, s.p, s.r, is);
	printf("intersections: %d\n", r);
	for (size_t i = 0; i < r; ++i) {
		printf("  at: %.2f, %.2f, %.2f\n", is[i].x, is[i].y, is[i].z);
	}

	//image_save(&img, "out.png");
	image_destroy(&img);

	return 0;
}
