#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct {
	vec3 p;
	vec3 d;
} Ray;

typedef struct {
	vec3 p;
	vec3 n;
} RayHit;

RayHit rayhit_new(vec3 p, vec3 n) {
	RayHit rh;
	rh.p = p;
	rh.n = vec3_normalize(n);
	return rh;
}

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

int ray_intersects_sphere(Ray *ray, const vec3 c, const float r, RayHit is[2]) {
	/* from ray origin to sphere */
	vec3 vpc = vec3_sub(c, ray->p);
	
	/* ray can intersect with sphere as it is in front of it */
	if (vec3_dot(ray->d, vpc) > 0.0f) {
		vec3 pc = ray_project_point(ray, c);
		float dist = fabsf(vec3_len(vec3_sub(pc, c)));
		if (dist > r) {
			// no intersection
			return 0;
		} else if (dist == r) {
			// one intersection
			is[0].p = pc;
			is[0].n = vec3_normalize(vec3_sub(pc, c));
			return 1;
		} else {
			// two intersections
			float pci = sqrtf(r*r + dist*dist);
			
			is[0].p = vec3_add(pc, vec3_mult(ray->d, pci));
			is[1].p = vec3_sub(pc, vec3_mult(ray->d, pci));
			
			vec3 n1 = vec3_normalize(vec3_sub(is[0].p, c));
			vec3 n2 = vec3_normalize(vec3_sub(is[1].p, c));
			//is[0].n = vec3_normalize(vec3_sub(ray->d, vec3_mult(n1, 2.0f * vec3_dot(ray->d, n1))));
			//is[1].n = vec3_normalize(vec3_sub(ray->d, vec3_mult(n2, 2.0f * vec3_dot(ray->d, n2))));
			is[0].n = n1;
			is[1].n = n2;
			
			/* sort by distance */
			float lp1 = vec3_len(vec3_sub(is[0].p, ray->p));
			float lp2 = vec3_len(vec3_sub(is[1].p, ray->p));
			if (lp1 > lp2) {
				RayHit tmp = is[0];
				is[0] = is[1];
				is[1] = tmp;
			}
			return 2;
		}
	} else {
		// behind the ray
		return 0;
	}

	return 0;
}

#endif
