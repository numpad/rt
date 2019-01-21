#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct {
	vec3 p;
	vec3 d;
} Ray;

Ray ray_new(vec3 origin, vec3 dir) {
	Ray ray;
	ray.p = origin;
	ray.d = vec3_normalize(dir);
	return ray;
}

vec3 ray_project_point(Ray *ray, vec3 q) {
	vec3 u = vec3_sub(q, ray->p);

	vec3 puv = vec3_mult(ray->d, vec3_dot(ray->d, u) / vec3_len(ray->d));
	return vec3_add(ray->p, puv);
}

int ray_intersects_sphere(Ray *ray, const vec3 c, const float r, vec3 is[2]) {
	/* from ray origin to sphere */
	vec3 vpc = vec3_sub(c, ray->p);

	/* ray can intersect with sphere as it is in front of it */
	if (vec3_dot(ray->d, vpc) > 0) {
		vec3 pc = ray_project_point(ray, c);
		float dist = fabsf(vec3_len(vec3_sub(pc, c)));
		if (dist > r) {
			// no intersection
			return 0;
		} else if (dist == r) {
			// one intersection
			is[0] = pc;
			return 1;
		} else {
			// two intersections
			
			float pci = sqrtf(r*r + dist*dist);

			is[0] = vec3_add(pc, vec3_mult(ray->d, pci));
			is[1] = vec3_sub(pc, vec3_mult(ray->d, pci));
			return 2;
		}
	} else {
		return 0;
	}

	return 0;
}

#endif
