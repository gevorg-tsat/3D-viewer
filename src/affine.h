/* ==========================================================================*/
/* Copyright 2023 © Moscow, Russian Federaion
 *
 * This file contains Original Code created by
 * Artem Turin aka trunkslo,
 * Gevorg Tsaturyan aka knothulk and
 * Igor Baidikov aka lorenttr.
 *
 * The Original Code and all software developed in the process of
 * participation on learning by experimental programming educational method.
 * The whole methodology was developed and distributed by
 * Autonomous non-profit organization «School 21» (ANO «School 21»).
 *
 * Redistribution and use of this file, its parts, or entire project
 * are permitted by confirmation of its original creators.
 */
/* ==========================================================================*/

/**
 * @author trunkslo, knothulk & lorenttr
 * @mainpage
 * 3dViewer_v1.0, backend realised in C language, gui written
 *on QT Creator
 *
 * Implementation of a program to visualise 3D wireframe models
 *
 * The program provide the ability to:
 * Load a wireframe model from an obj file (vertices and surfaces list support
 *only). Translate the model by a given distance in relation to the X, Y, Z
 * axes. Rotate the model by a given angle relative to its X, Y, Z axes. Scale
 * the model by a given value.
 *
 * The program allow customizing the type of projection (parallel and central)
 * The program allow setting up the type (solid, dashed), color and thickness
 *of the edges, display method (none, circle, square), color and size of the
 * vertices
 * The program allow choosing the background color
 * Settings saved between program restarts
 *
 * The program allow saving the captured (rendered) images as bmp and jpeg
 * files. The program allow recording small screencasts by a special button -
 * the current custom affine transformation of the loaded object into
 * gif-animation (640x480, 10fps, 5s)
 */

#pragma once

#include "file_to_object.h"

// Affine transformations

/**
 * @brief Fucntion fo translate model by a given distance by x axis
 *
 * @param obj --- pointer to object structure
 * @param shift --- value of the shift
 */
void translate_ox_object(file_data *obj, double shift);

/**
 * @brief Fucntion fo translate model by a given distance by y axis
 *
 * @param obj --- pointer to object structure
 * @param shift --- value of the shift
 */
void translate_oy_object(file_data *obj, double shift);

/**
 * @brief Fucntion fo translate model by a given distance by z axis
 *
 * @param obj --- pointer to object structure
 * @param shift --- value of the shift
 */
void translate_oz_object(file_data *obj, double shift);

/**
 * @brief Fucntion fo rotate model by a given angle relative to its X axis
 *
 * @param obj - pointer to object structure
 * @param angle - value of the angle to rotate
 */
void rotate_ox_object(file_data *obj, double angle);

/**
 * @brief Fucntion fo rotate model by a given angle relative to its Y axis
 *
 * @param obj - pointer to object structure
 * @param angle - value of the angle to rotate
 */
void rotate_oy_object(file_data *obj, double angle);

/**
 * @brief Fucntion fo rotate model by a given angle relative to its Z axis
 *
 * @param obj - pointer to object structure
 * @param angle - value of the angle to rotate
 */
void rotate_oz_object(file_data *obj, double angle);

/**
 * @brief Fucntion fo scale model by a given value
 *
 * @param obj - pointer to object structure
 * @param scale - value to scale
 */
void scale_object(file_data *obj, double scale);