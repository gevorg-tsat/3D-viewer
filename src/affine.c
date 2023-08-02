#include "affine.h"

#include <math.h>

void translate_ox_object(file_data *obj, double shift) {
  for (size_t i = 0; i < obj->vertices_count; i += 3) obj->vertices[i] += shift;
}

void translate_oy_object(file_data *obj, double shift) {
  for (size_t i = 1; i < obj->vertices_count; i += 3) obj->vertices[i] += shift;
}

void translate_oz_object(file_data *obj, double shift) {
  for (size_t i = 2; i < obj->vertices_count; i += 3) obj->vertices[i] += shift;
}

void rotate_ox_object(file_data *obj, double angle) {
  for (size_t i = 0; i < obj->vertices_count; i += 3) {
    double y = obj->vertices[i + 1];
    double z = obj->vertices[i + 2];
    obj->vertices[i + 1] = y * cos(angle) - z * sin(angle);
    obj->vertices[i + 2] = y * sin(angle) + z * cos(angle);
  }
}

void rotate_oy_object(file_data *obj, double angle) {
  for (size_t i = 1; i < obj->vertices_count; i += 3) {
    double x = obj->vertices[i - 1];
    double z = obj->vertices[i + 1];
    obj->vertices[i - 1] = x * cos(angle) + z * sin(angle);
    obj->vertices[i + 1] = -x * sin(angle) + z * cos(angle);
  }
}

void rotate_oz_object(file_data *obj, double angle) {
  for (size_t i = 2; i < obj->vertices_count; i += 3) {
    double x = obj->vertices[i - 2];
    double y = obj->vertices[i - 1];
    obj->vertices[i - 2] = x * cos(angle) - y * sin(angle);
    obj->vertices[i - 1] = x * sin(angle) + y * cos(angle);
  }
}

void scale_object(file_data *obj, double scale) {
  for (size_t i = 0; i < obj->vertices_count; ++i) obj->vertices[i] *= scale;
}