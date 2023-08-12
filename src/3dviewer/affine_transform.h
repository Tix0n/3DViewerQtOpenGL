#ifndef AFFINE_TRANSFORM
#define AFFINE_TRANSFORM

#include <math.h>
#include <stdio.h>
/**
    @brief Shifts the model along the selected axis by the specified value
    @param matrix_of_vertex Matrix of model vertices
    @param axis Selected axis (0 - X, 1 - Y, 2 - Z)
    @param number Number of coordinates of model points
    @param value Shift value
*/
void move_model(float *matrix_of_vertex, int axis, int number, float value);
/**
    @brief Rotates the model around the OX axis by the specified angle
    @param matrix_of_vertex Matrix of model vertices
    @param number Number of model vertices
    @param angle Angle of rotation in radians
*/
void rotation_by_ox(float *matrix_of_vertex, int number, float angle);
/**
    @brief Rotates the model around the OY axis by the specified angle
    @param matrix_of_vertex Matrix of model vertices
    @param number Number of model vertices
    @param angle Angle of rotation in radians
*/
void rotation_by_oy(float *matrix_of_vertex, int number, float angle);
/**
    @brief Rotates the model around the OZ axis by the specified angle
    @param matrix_of_vertex Matrix of model vertices
    @param number Number of model vertices
    @param angle Angle of rotation in radians
*/
void rotation_by_oz(float *matrix_of_vertex, int number, float angle);
/**
    @brief Scales the model by the specified factor
    @param matrix_of_vertex Matrix of model vertices
    @param number Number of coordinates of model points
    @param value Scaling factor
*/
void scale_model(float *matrix_of_vertex, int number, float value);

#endif  // AFFINE_TRANSFORM