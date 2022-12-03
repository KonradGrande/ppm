#include "ppm.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

color_t color(uint32_t color) {
  color_t c;
  c.r = (color & 0xff0000) >> 8 * 2;
  c.g = (color & 0x00ff00) >> 8 * 1;
  c.b = (color & 0x0000ff) >> 8 * 0;
  return c;
}

char *color_format(color_t c) {
  char *str = malloc(9);
  if (!str) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }

  sprintf(str, "#%.2x%.2x%.2x", c.r, c.g, c.b);
  return str;
}

bool color_eq(color_t a, color_t b) {
  if (a.r != b.r)
    return false;
  if (a.g != b.g)
    return false;
  if (a.b != b.b)
    return false;
  return true;
}

image_t *image_init(int width, int height) {
  image_t *img = malloc(sizeof(image_t));
  if (!img)
    goto error;

  img->width = width;
  img->height = height;
  img->pixels = calloc(width * height, sizeof(color_t));
  if (!img->pixels)
    goto error;

  return img;
error:
  perror("malloc");
  exit(EXIT_FAILURE);
}

void image_free(image_t *img) {
  free(img->pixels);
  free(img);
}

void image_pixel_set(image_t *img, int x, int y, color_t pixel) {
  assert(y < img->height && x < img->width);
  img->pixels[y * img->width + x] = pixel;
}

void image_write(char *filename, image_t *img) {
  FILE *f = fopen(filename, "w");
  if (!f) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  fprintf(f, "%s\n", MAGIC_NUMBER);
  fprintf(f, "%d %d\n", img->width, img->height);
  fprintf(f, "%d\n", 0xff);

  fwrite(img->pixels, sizeof(color_t), img->width * img->height, f);
  fclose(f);
}

image_t *image_read(char *filename) {
  int width, height, max_value;
  char *magic_number;
  image_t *img = NULL;

  FILE *f = fopen(filename, "r");
  if (!f) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  fscanf(f, "%ms", &magic_number);
  if (strcmp(magic_number, MAGIC_NUMBER) == 0) {
    fscanf(f, "%d %d", &width, &height);
    fscanf(f, "%d", &max_value);
    img = image_init(width, height);
    fscanf(f, "%s", (char *)img->pixels);
  }
  free(magic_number);
  fclose(f);
  return img;
}

void image_eq(image_t *a, image_t *b) {
  assert(a->width == b->width);
  assert(a->height == b->height);
  for (int i = 0; i < a->height * a->width; i++)
    assert(color_eq(a->pixels[i], b->pixels[i]) == true);
}
