#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#define VEC3_POW2(a) ((a)*(a))

typedef struct {
	float x, y, z;
} vec3;

vec3 vec3_new(const float x, const float y, const float z) {
	vec3 vec;
	vec.x = x;
	vec.y = y;
	vec.z = z;
	return vec;
}

vec3 vec3_add(const vec3 a, const vec3 b) {
	vec3 res;
	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return res;
}

vec3 vec3_sub(const vec3 a, const vec3 b) {
	vec3 res;
	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return res;
}

vec3 vec3_mul(const vec3 a, const vec3 b) {
	vec3 res;
	res.x = a.x * b.x;
	res.y = a.y * b.y;
	res.z = a.z * b.z;
	return res;
}

vec3 vec3_mult(const vec3 a, const float s) {
	vec3 res;
	res.x = a.x * s;
	res.y = a.y * s;
	res.z = a.z * s;
	return res;
}

vec3 vec3_div(const vec3 a, const float s) {
	vec3 res;
	res.x = a.x / s;
	res.y = a.y / s;
	res.z = a.z / s;
	return res;
}

float vec3_len(const vec3 a) {
	return sqrtf(
		VEC3_POW2(a.x) +
		VEC3_POW2(a.y) +
		VEC3_POW2(a.z)
	);
}

float vec3_dot(const vec3 a, const vec3 b) {
	return a.x * b.x +
	       a.y * b.y +
	       a.z * b.z;
}

vec3 vec3_normalize(const vec3 a) {
	return vec3_div(a, vec3_len(a));
}

#endif
