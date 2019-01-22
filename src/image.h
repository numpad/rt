#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stb/stb_image_write.h"

typedef struct {
	unsigned char *pixels;
	unsigned int width, height;
} Image;

Image image_new(unsigned int w, unsigned int h) {
	Image img;
	img.pixels = malloc(w * h * 3 * sizeof(unsigned char));
	img.width = w;
	img.height = h;
	return img;
}

void image_destroy(Image *img) {
	free(img->pixels);
}

void image_fill(Image *img, int r, int g, int b) {
	for (size_t i = 0; i < img->width * img->height * 3; i += 3) {
		img->pixels[i + 0] = r;
		img->pixels[i + 1] = g;
		img->pixels[i + 2] = b;
	}
}

void image_set(Image *img, int x, int y, int r, int g, int b) {
	if (x < 0 || y < 0 || x >= img->width || y >= img->height) {
		printf("out of bounds. (pos = %d, %d)", x, y);
		return;
	}
	
	if (r > 255) r = 255;
	else if (r < 0) r = 0;
	if (g > 255) g = 255;
	else if (g < 0) g = 0;
	if (b > 255) b = 255;
	else if (b < 0) b = 0;
	
	img->pixels[(x + y * img->width) * 3 + 0] = r;
	img->pixels[(x + y * img->width) * 3 + 1] = g;
	img->pixels[(x + y * img->width) * 3 + 2] = b;
}

void image_save(Image *img, const char *filename) {
	stbi_write_png(filename, img->width, img->height, 3, img->pixels, img->width * 3 * sizeof(unsigned char));
}

#endif
