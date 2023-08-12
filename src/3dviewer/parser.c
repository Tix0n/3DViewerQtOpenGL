#include "parser.h"

int parser(char *name_of_file, struct info_figure *figure) {
  int res = -1;
  int flag_vertex = 0, flag_faces = 0;
  FILE *file = NULL;
  size_t len = 0;
  ssize_t read = 0;
  figure->number_of_faces_all = 0;
  figure->number_of_vertex = 0;
  file = fopen(name_of_file, "r");
  if (file != NULL) {
    char *lbuf = NULL;
    while ((read = getline(&lbuf, &len, file)) != -1) {
      if (lbuf[0] == 'v' && lbuf[1] == ' ') {
        figure->number_of_vertex++;
        flag_vertex = 1;

      } else if (lbuf[0] == 'f' && lbuf[1] == ' ') {
        for (int i = 1; lbuf[i] != '\n'; i++) {
          if (lbuf[i] == ' ') {
            figure->number_of_faces_all++;
          }
        }
        flag_faces = 1;
      }
    }
    fclose(file);
    if (lbuf) free(lbuf);
    res = second_open(name_of_file, figure);
  } else {
    res = 0;
  }
  if (res != 0 && flag_vertex > 0 && flag_faces > 0)
    res = 1;
  else
    res = 0;
  return res;
}

int second_open(char *name_of_file, struct info_figure *figure) {
  int res = 0, flag_vertex = 0, flag_faces = 0;
  FILE *file = NULL;
  size_t len = 0;
  ssize_t read = 0;
  mem_alloc_matrices(figure);
  file = fopen(name_of_file, "r");
  int i = 0, count = 0, ind_now = 0, count_vertex_in_str = 0;
  setlocale(LC_NUMERIC, "en_US.UTF-8");
  char digits_str[64] = "\0", *lbuf = NULL;
  unsigned int temp_ind_in_str[256];
  for (; (read = getline(&lbuf, &len, file)) != -1; count++) {
    if ((int)read > 1 && lbuf[0] == 'v' && lbuf[1] == ' ') {
      sscanf(lbuf, "v %f %f %f", &figure->matrix_of_vertex_origin[i],
             &figure->matrix_of_vertex_origin[i + 1],
             &figure->matrix_of_vertex_origin[i + 2]);
      found_max_min(figure->matrix_of_vertex_origin[i],
                    figure->matrix_of_vertex_origin[i + 1],
                    figure->matrix_of_vertex_origin[i + 2], figure, i);
      i += 3;
      flag_vertex = 1;
    } else if (lbuf[0] == 'f' && lbuf[1] == ' ') {
      count_vertex_in_str = 0;
      for (int j = 1; j < (int)(read - 1); j++) {
        if (lbuf[j] == ' ') {
          j++;
          memset(digits_str, 0, sizeof(digits_str));
          for (int k = 0; lbuf[j] != '\n' && lbuf[j] != '/' && lbuf[j] != ' ';
               j++) {
            if (lbuf[j] != '-') {
              digits_str[k] = lbuf[j];
              k++;
            }
          }
          unsigned int temp = (unsigned int)(atoi(digits_str));
          if (temp > 0) {
            temp_ind_in_str[count_vertex_in_str] = temp - 1;
            count_vertex_in_str++;
          }
        }
      }
      connection_from_faces_to_edges(temp_ind_in_str, figure,
                                     &count_vertex_in_str, &ind_now);
      flag_faces = 1;
    }
  }
  fclose(file);
  if (lbuf) free(lbuf);
  if (flag_vertex > 0 && flag_faces > 0) res = 1;
  return res;
}

void mem_alloc_matrices(struct info_figure *figure) {
  figure->matrix_of_vertex =
      (float *)calloc(figure->number_of_vertex * 3, sizeof(float));
  figure->matrix_of_vertex_origin =
      (float *)calloc(figure->number_of_vertex * 3, sizeof(float));
  figure->matrix_of_index = (unsigned int *)calloc(
      figure->number_of_faces_all * 2, sizeof(unsigned int));
}

void connection_from_faces_to_edges(unsigned int temp_ind_in_str[],
                                    struct info_figure *figure,
                                    int *count_vertex_in_str, int *ind_now) {
  for (int j = 0; j < *count_vertex_in_str * 2; (*ind_now)++, j++) {
    if (j == 0) {
      figure->matrix_of_index[*ind_now] = temp_ind_in_str[j];
      figure->matrix_of_index[*ind_now + 1] = temp_ind_in_str[j + 1];
    } else if (j == *count_vertex_in_str - 1) {
      figure->matrix_of_index[*ind_now + j] = temp_ind_in_str[j];
      figure->matrix_of_index[*ind_now + j + 1] = temp_ind_in_str[j - j];
    } else if (j > 0 && j < *count_vertex_in_str) {
      figure->matrix_of_index[*ind_now + j] = temp_ind_in_str[j];
      figure->matrix_of_index[*ind_now + j + 1] = temp_ind_in_str[j + 1];
    }
  }
}

void found_max_min(float x, float y, float z, struct info_figure *figure,
                   int i) {
  if (x > figure->x_max || i == 0) figure->x_max = x;
  if (x < figure->x_min || i == 0) figure->x_min = x;
  if (y > figure->y_max || i == 0) figure->y_max = y;
  if (y < figure->y_min || i == 0) figure->y_min = y;
  if (z > figure->z_max || i == 0) figure->z_max = z;
  if (z < figure->z_min || i == 0) figure->z_min = z;
}

void free_matrix(struct info_figure *figure) {
  figure->number_of_faces_all = 0;
  figure->number_of_vertex = 0;
  free(figure->matrix_of_index);
  free(figure->matrix_of_vertex);
  free(figure->matrix_of_vertex_origin);
}

void open_file(char *filename, struct info_figure *figure) {
  figure->load_result = parser(filename, figure);
}
