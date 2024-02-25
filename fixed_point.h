#ifndef MATRIX_MUL_FIXED_POINT_H
#define MATRIX_MUL_FIXED_POINT_H

// Multiplication of two matrices with any sizes using floating point.
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

#define FIXED_POINT_FRACTIONAL_BITS 24

extern float fixedToFloat(int32_t input);
extern int32_t floatToFixed(float input);
extern bool IntEq(int32_t a, int32_t b, int32_t precision);

extern int32_t** createIntMatrix(uint32_t rows, uint32_t columns);
extern int64_t** createLongIntMatrix(uint32_t rows, uint32_t columns);

extern int32_t** multiplyIntMatrices(int32_t** matrix1, int32_t** matrix2, uint32_t rows1, uint32_t columns1, uint32_t rows2, uint32_t columns2);

#endif //MATRIX_MUL_FIXED_POINT_H
