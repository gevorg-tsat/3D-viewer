#ifndef PARSER_H_
#define PARSER_H_
// #pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*!
 * @brief Structure to store vertices and facets info, such as coordinates and
 * amount.
 *
 */
typedef struct file_data {
  unsigned vertices_count;
  unsigned triangle_cnt;
  unsigned square_cnt;
  unsigned *facets_coor_triangle;
  unsigned *facets_coor_square;
  double *vertices;
} file_data;

/*!
 * @public
 * @brief Parse data from .obj-file to file_data-structure.
 * @param filename Filepath
 * @param obj Pointer to a object of structure where to store data from file
 * @return 1 if any error, else 0
 */
int parse_file(char *filename, file_data *obj);

/*!
 * @brief clear data from file_data-structure object
 *
 * @param obj Pointer to a object of structure
 */
void clear_obj(file_data *obj);

#endif  //  PARSER_H_