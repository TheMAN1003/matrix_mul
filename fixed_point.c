#include "fixed_point.h"
#include "floating_point.h"

float fixedToFloat(int32_t input) {
    return ((float)input / (float)(1 << FIXED_POINT_FRACTIONAL_BITS));
}

int32_t floatToFixed(float input) {
    if (-1.001 <= input && input <= 1.001 ) {
        return (int32_t) (floorf(input * (float)(1 << FIXED_POINT_FRACTIONAL_BITS)));
    } else {
        return INT_MIN;
    }
}

bool IntEq(int32_t a, int32_t b, int32_t precision) {
    if (abs(a - b) < precision){
        return 1;
    } else {
        return 0;
    }
}

int32_t **createIntMatrix(uint32_t rows, uint32_t columns) {
    int32_t** matrix = (int32_t**) malloc(rows * sizeof(int32_t*));
    if (!matrix) {
        return NULL;
    }
    for (uint32_t i = 0; i < rows; ++i){
        matrix[i] = (int32_t*) malloc(columns * sizeof(int32_t));
        if (!matrix[i]){
            for (uint32_t j = 0; j < i; ++j) {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}

int64_t **createLongIntMatrix(uint32_t rows, uint32_t columns) {
    int64_t** matrix = (int64_t**) malloc(rows * sizeof(int64_t*));
    if (!matrix) {
        return NULL;
    }
    for (uint32_t i = 0; i < rows; ++i){
        matrix[i] = (int64_t*) malloc(columns * sizeof(int64_t));
        if (!matrix[i]){
            for (uint32_t j = 0; j < i; ++j) {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}

int32_t** multiplyIntMatrices(int32_t **matrix1, int32_t **matrix2, uint32_t rows1, uint32_t columns1, uint32_t rows2,
                              uint32_t columns2) {
    if (!isMultiplicable(columns1, rows2)) {
        return NULL;
    }

    int64_t **temp = createLongIntMatrix(rows1, columns2);
    int32_t **result = createIntMatrix(rows1, columns2);
    if (!temp || !result) {
        return NULL;
    }
    for (uint32_t i = 0; i < rows1; ++i) {
        for (uint32_t j = 0; j < columns2; ++j) {
            temp[i][j] = 0;
            for (uint32_t k = 0; k < columns1; ++k) {
                temp[i][j] += (int64_t) matrix1[i][k] * (int64_t) matrix2[k][j];
            }
            result[i][j] = (int32_t)(temp[i][j] >> FIXED_POINT_FRACTIONAL_BITS);
        }
    }
    return result;
}
