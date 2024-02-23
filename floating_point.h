#ifndef MATRIX_MUL_FLOATING_POINT_H
#define MATRIX_MUL_FLOATING_POINT_H

// Multiplication of two matrices with any sizes using floating point.
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#define ASSERT_TRUE(condition) if (!(condition)) { printf("Failed assertion: %s\n", #condition); exit(1); }
#define ASSERT_FALSE(condition) ASSERT_TRUE(!(condition))
#define ASSERT_EQUAL(expected, actual) ASSERT_TRUE(expected == actual)
#define ASSERT_NULL(ptr) ASSERT_TRUE(ptr == NULL)
#define ASSERT_NOT_NULL(ptr) ASSERT_TRUE(ptr != NULL)


extern float** createMatrix(uint32_t rows, uint32_t columns);
extern void freeMatrix(float** matrix, uint32_t rows);

extern bool isMultiplicable(uint32_t columns1, uint32_t rows2);
extern bool floatEq(float a, float b, float prec);

extern float** multiplyMatrices(float** matrix1, float** matrix2, uint32_t rows1, uint32_t columns1, uint32_t rows2, uint32_t columns2);












#endif //MATRIX_MUL_FLOATING_POINT_H