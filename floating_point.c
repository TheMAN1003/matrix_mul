#include "floating_point.h"

float** createMatrix(uint32_t rows, uint32_t columns) {
    float** matrix = (float**) malloc(rows * sizeof(float*));
    if (!matrix) {
        return NULL;
    }
    for (uint32_t i = 0; i < rows; ++i){
        matrix[i] = (float*) malloc(columns * sizeof(float));
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

void freeMatrix(float **matrix, uint32_t rows) {
    for (uint32_t i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

bool isMultiplicable(uint32_t columns1, uint32_t rows2) {
    if (columns1 == rows2) {
        return 1;
    } else {
        return 0;
    }
}

bool floatEq(float a, float b, float precision) {
    if (fabsf(a - b) < precision){
        return 1;
    } else {
        return 0;
    }
}

float** multiplyMatrices(float** matrix1, float** matrix2, uint32_t rows1, uint32_t columns1, uint32_t rows2, uint32_t columns2) {
    if (!isMultiplicable(columns1, rows2)){
        return NULL;
    }
    float** result = createMatrix(rows1, columns2);
    if (!result){
        return NULL;
    }
    for (uint32_t i = 0; i < rows1; ++i) {
        for (uint32_t j = 0; j < columns2; ++j) {
            result[i][j] = (float) 0;
            for (uint32_t k = 0; k < columns1; ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return result;
}