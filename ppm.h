#ifndef PPM_H_
#define PPM_H_

#include <stdbool.h>
#include <stdint.h>

#define MAGIC_NUMBER "P6"

typedef struct color {
  /* 0xRRGGBB */
  uint8_t r, g, b;
} color_t;

typedef struct image {
  int width, height, num_pixels;
  color_t *pixels;
} image_t;

color_t color(uint32_t color);
bool color_eq(color_t a, color_t b);
char *color_format(color_t c);

image_t *image_init(int width, int height);
void image_free(image_t *img);
void image_pixel_set(image_t *img, int x, int y, color_t pixel);
color_t image_pixel_get(image_t *img, int x, int y);
void image_write(char *filename, image_t *img);
image_t *image_read(char *filename);
void image_eq(image_t *a, image_t *b);

#endif // PPM_H_
