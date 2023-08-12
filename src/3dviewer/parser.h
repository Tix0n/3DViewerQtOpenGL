#ifndef PARSER_H
#define PARSER_H

#include <getopt.h>
#include <locale.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/**
  @brief A structure containing information about a shape.

  The "info_figure" structure contains information about the shape,
  including the number of vertices, the number of faces, the vertex and index
  matrices, as well as the minimum and maximum values for each of the axes and
  the matrix of the original vertices, as well as information about the success
  of opening the file.
*/
struct info_figure {
  int number_of_vertex;            ///< The number of vertices.
  int number_of_faces_all;         ///< The number of faces.
  float *matrix_of_vertex;         //< The matrix of vertices.
  unsigned int *matrix_of_index;   ///< The matrix of vertices.
  float x_max,                     ///< The maximum value on the X-axis.
      x_min,                       ///< The minimum value on the X-axis.
      y_max,                       ///< The maximum value on the Y-axis.
      y_min,                       ///< The minimum value on the Y-axis.
      z_max,                       ///< The maximum value on the Z-axis.
      z_min;                       ///< The minimum value on the Z-axis.
  bool load_result;                ///< The result of the download.
  float *matrix_of_vertex_origin;  ///< The matrix of the original vertices.
};
/**
  @brief Performs file parsing .obj with the geometric information of the shape
  and returns the result
  @param name_of_file The name of the file containing geometric information
  @param figure The structure in which the geometric information of the shape is
  recorded
  @return 0 - failed to open the file, 1 - successfully read information from
  the file
*/
int parser(char *name_of_file, struct info_figure *figure);
/**
  @brief Reads information from a file .obj and writes it to the info_figure
  structure
  @param name_of_file The name of the file containing geometric information
  @param figure The structure in which the geometric information of the shape is
  recorded
  @return 0 - failed to read information from the file, 1 - successfully read
  information from the file
*/
int second_open(char *name_of_file, struct info_figure *figure);
/**
  @brief Performs a connection between vertices and edges
  @param temp_ind_in_str Temporary array of vertex indexes
  @param figure The structure that contains information about the shape
  @param count_vertex_in_str Number of vertices in a row
  @param ind_now The current index in the matrix_of_index array
*/
void connection_from_faces_to_edges(unsigned int temp_ind_in_str[],
                                    struct info_figure *figure,
                                    int *count_vertex_in_str, int *ind_now);
/**
  @brief Allocates memory for geometric information matrices of a shape
  @param figure The structure for which memory is allocated
*/
void mem_alloc_matrices(struct info_figure *figure);
/**
  @brief Finds the maximum and minimum values of the x, y, z coordinates and
  stores them in the info_figure structure.
  @param X coordinate of the current vertex
  @param Y coordinate of the current vertex
  @param Z coordinate of the current vertex
  @param figure A pointer to the info_figure structure in which the maximum and
  minimum values will be stored
  @param i Index of the current vertex
*/
void found_max_min(float x, float y, float z, struct info_figure *figure,
                   int i);
/**
  @brief Frees up the memory allocated for the matrices and resets the variables
  responsible for the size of the matrices.
  @param figureA pointer to the info_figure structure whose memory needs to be
  freed
*/
void free_matrix(struct info_figure *figure);
/**
  @brief Runs a function that parses the shape data from the file passed as an
  argument and saves the error code to the structure
  @param filename Name of the file with data about the shape
  @param figure Pointer to the info_figure structure to which the read data will
  be written
*/
void open_file(char *filename, struct info_figure *figure);

#endif  // PARSER_H
