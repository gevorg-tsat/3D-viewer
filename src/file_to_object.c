#include "file_to_object.h"
#define LINE_MAX_SIZE 512

/**
 * @brief deletes whitespaces
 *
 * @param str
 */
void right_trim(char *str) {
  for (int i = strlen(str) - 1; i >= 0 && strchr(" \n\r", str[i]); i--)
    str[i] = '\0';
}
/**
 * @brief adds coordinates of vertice into file_data-object
 *
 * @param s string from .obj file which starts with "v"
 * @param obj
 * @param index
 * @return 1 if error, else 0
 */
int add_vertices(char *s, file_data *obj, unsigned index) {
  char flag_skip;
  double x, y, z;
  int args = sscanf(s, "%c %lf %lf %lf", &flag_skip, &x, &y, &z);
  if (args != 4) return 1;
  obj->vertices[index] = x;
  obj->vertices[index + 1] = y;
  obj->vertices[index + 2] = z;
  return 0;
}
/**
 * @brief counts amount of vertices in facet
 *
 * @param arg string from .obj file which starts with "f"
 * @return unsigned
 */
unsigned count_vert(char *arg) {
  right_trim(arg);
  int vert_num;
  unsigned cnt = 0;
  arg = strtok(arg, " ");
  int arg_cnt = 0;
  while ((arg = strtok(NULL, " ")) != NULL) {
    arg_cnt = sscanf(arg, "%d", &vert_num);
    if (!arg_cnt) return -1;
    cnt++;
  }

  // cnt--;
  return cnt;
}
/**
 * @brief adds facet-data into file_data-object
 *
 * @param s string from .obj file which starts with "f"
 * @param obj
 * @param triangle_ind
 * @param square_ind
 * @return int
 */
int add_facets(char *s, file_data *obj, unsigned *triangle_ind,
               unsigned *square_ind) {
  char temp[LINE_MAX_SIZE];
  strcpy(temp, s);
  unsigned cnt = count_vert(temp);
  char *arg = strtok(s, " ");
  //   if (cnt == -1)
  //     puts(temp);

  unsigned *dest;
  unsigned *index;
  if (cnt == 3) {
    dest = obj->facets_coor_triangle;
    index = triangle_ind;
  } else if (cnt == 4) {
    dest = obj->facets_coor_square;
    index = square_ind;
  } else
    cnt = 0;
  int vert_num;

  for (unsigned i = 0; i < cnt; i++) {
    arg = strtok(NULL, " ");
    int arg_cnt = sscanf(arg, "%d", &vert_num);
    if (!arg_cnt) return -1;
    dest[*index + i] = vert_num - 1;
  }
  (*index) += cnt;
  return cnt;
}
void clear_obj(file_data *obj) {
  obj->triangle_cnt = obj->vertices_count = obj->square_cnt = 0;
  free(obj->facets_coor_triangle);
  free(obj->vertices);
  free(obj->facets_coor_square);
}
/**
 * @brief counts amount of facets and vertices in .obj-file
 *
 * @param file
 * @param obj
 */
void count_FV(FILE *file, file_data *obj) {
  obj->vertices_count = 0;
  obj->triangle_cnt = 0;
  obj->square_cnt = 0;
  fseek(file, 0, SEEK_SET);
  char buff[LINE_MAX_SIZE];
  while (!feof(file)) {
    fgets(buff, LINE_MAX_SIZE - 1, file);
    if (buff[0] == 'v' && buff[1] == ' ')
      (obj->vertices_count) += 3;
    else if (buff[0] == 'f' && buff[1] == ' ') {
      right_trim(buff);
      // puts(buff);
      unsigned cnt = count_vert(buff);
      if (cnt == 3)
        obj->triangle_cnt += 1;
      else if (cnt == 4)
        obj->square_cnt += 1;
    }
  }
}

int parse_file(char *filename, file_data *obj) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    return 1;
  }
  count_FV(file, obj);
  fseek(file, 0, SEEK_SET);
  char buff[LINE_MAX_SIZE];
  unsigned vert_ind = 0, triangle_ind = 0, square_ind = 0;
  obj->vertices = calloc(obj->vertices_count, sizeof(double));
  obj->facets_coor_square = calloc(obj->square_cnt * 4, sizeof(unsigned));
  obj->facets_coor_triangle = calloc((obj->triangle_cnt) * 3, sizeof(unsigned));
  while (!feof(file)) {
    fgets(buff, LINE_MAX_SIZE - 1, file);
    right_trim(buff);
    if (buff[0] == 'v' && buff[1] == ' ') {
      int error = add_vertices(buff, obj, vert_ind);
      if (error) {
        free(obj->vertices);
        free(obj->facets_coor_triangle);
        free(obj->facets_coor_square);
        fclose(file);
        return 1;
      }
      vert_ind += 3;
    } else if (buff[0] == 'f' && buff[1] == ' ') {
      add_facets(buff, obj, &triangle_ind, &square_ind);
    }
  }
  fclose(file);
  return 0;
}

// TESTING
// int main() {
//     char *path = "cube.obj";
//     file_data obj;
//     int error = parse_file(path, &obj);
//     if (error) {
//         printf("ERRROOORRRRRR\n\n");
//         return 1;
//     }
//     for (int i = 0; i < obj.vertices_count; i++)
//         printf("%lf ", obj.vertices[i]);
//     printf("SQUARE:\n");
//     for (int i = 0; i < obj.square_cnt; i++)
//         printf("%lld ", obj.facets_coor_square[i]);
//     printf("\n");
//     printf("TRIANGLE:\n");
//     for (int i = 0; i < obj.triangle_cnt; i++)
//         printf("%lld ", obj.facets_coor_triangle[i]);

//     return 0;
// }
