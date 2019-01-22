#include <stdio.h>
#define M_PI 3.141592653
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
	float i;
	float r, g, b;
} Light;

Light light_new(vec3 p, float i, float r, float g, float b) {
	Light l;
	l.p = p;
	l.i = i;
	l.r = r;
	l.g = g;
	l.b = b;
	return l;
}

typedef struct {
	vec3 p;
	float r;
	Material mat;
} Sphere;

Sphere sphere_new(vec3 p, float r, Material m) {
	Sphere s;
	s.p = p;
	s.r = r;

	s.mat = m;
	return s;
}

int main(int argc, char *argv[]) {
	Image img = image_new(800, 600);
	image_fill(&img, 215, 211, 255);
	
	Material red = material_new(242, 105, 85);
	Material blue = material_new(120, 94, 238);
	Material white = material_new(255, 255, 255);
	
	int spheres_n = 3;
	Sphere spheres[] = {
		sphere_new(vec3_new( 15.0f, -25.0f, 50.0f), 15.0f, red),
		sphere_new(vec3_new(-5.0f,  15.0f, 60.0f), 8.0f, blue),
		sphere_new(vec3_new(-5.0f, -15.0f, 70.0f), 16.0f, white)
	};
	
	int lights_n = 1;
	Light lights[] = {
		light_new(vec3_new(-50.0f, 40.0f, 10.0f), 1.0f, 1.0f, 1.0f, 1.0f),
		light_new(vec3_new(40.0f, -25.0f, 10.0f), 1.0f, 1.0f, 1.0f, 1.0f),
	};
	
	float fov = M_PI * 0.5f;
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
			
			for (int i = 0; i < spheres_n; ++i) {
				Sphere s = spheres[i];
				
				RayHit hits[2];
				int r = ray_intersects_sphere(&ray, s.p, s.r, hits);
				if (r > 0) {
					float illu = 0.2f;
					
					for (int light_i = 0; light_i < lights_n; ++light_i) {
						vec3 to_light = vec3_sub(lights[light_i].p, hits[0].p);
						
						float light = vec3_dot(hits[0].n, vec3_normalize(to_light));
						if (light < 0.0f) light = 0.0f;
						
						illu += light;
					}
					if (illu > 1.0f) illu = 1.0f;
					else if (illu < 0.0f) illu = 0.0f;
					
					int c[] = {
						s.mat.r * illu,
						s.mat.g * illu,
						s.mat.b * illu
					};
						
					image_set(&img, x, y, c[0], c[1], c[2]);
				}
			}
		}
	}
	
	image_save(&img, "out.png");
	
	image_destroy(&img);

	return 0;
}
