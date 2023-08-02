#ifndef PARSER_H_
#define PARSER_H_
//#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct coordinates {
  double x;
  double y;
  double z;
} coordinates;


typedef struct file_data {
  unsigned vertices_count;
  unsigned triangle_cnt;
  unsigned square_cnt;
  unsigned *facets_coor_triangle;
  unsigned *facets_coor_square;
  double *vertices;
} file_data;

unsigned count_vert(char * arg);
int parse_file(char *filename, file_data *obj);
void count_FV(FILE *file, file_data *obj);
int add_vertices(char *s, file_data *obj, unsigned index);
int add_facets(char *s, file_data *obj, unsigned* triangle_ind, unsigned* square_ind);
void clear_obj(file_data *obj);

#endif  //  PARSER_H_