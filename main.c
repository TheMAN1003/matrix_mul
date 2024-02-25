#include "floating_point.h"
#include "fixed_point.h"

void testMul1(){
    printf("Test1: are matrices ax3 and 3xb multiplicable (yes)\n");
    ASSERT_TRUE(isMultiplicable(3, 3))
    printf("Success!\n");
}

void testMul2(){
    printf("Test2: are matrices ax5 and 4xb multiplicable (no)\n");
    ASSERT_FALSE(isMultiplicable(5, 4))
    printf("Success!\n");
}

void testCreation1(){
    printf("Test3: creation of 5x5 matrix\n");
    uint32_t rows = 5;
    uint32_t columns = 5;
    ASSERT_NOT_NULL(createMatrix(rows, columns))
    printf("Success!\n");
}

void testCreation2(){
    printf("Test4: creation of -1x-1 matrix (impossible)\n");
    ASSERT_NULL(createMatrix(-1, -1))
    printf("Success!\n");
}

void testCreation3(){
    printf("Test5: creation of 50000x50000 matrix\n");
    uint32_t rows = 50000;
    uint32_t columns = 50000;
    ASSERT_NOT_NULL(createMatrix(rows, columns))
    printf("Success!\n");
}

void testFree1(){
    printf("Test6: freeing up the memory of 10x10 matrix\n");
    uint32_t rows = 10;
    uint32_t columns = 10;
    float** matrix = createMatrix(rows, columns);
    freeMatrix(matrix, rows);
    matrix = NULL;
    ASSERT_NULL(matrix)
    printf("Success!\n");
}

void testFree2(){
    printf("Test7: freeing up the memory of 50000x50000 matrix\n");
    uint32_t rows = 50000;
    uint32_t columns = 50000;
    float** matrix = createMatrix(rows, columns);
    freeMatrix(matrix, rows);
    matrix = NULL;
    ASSERT_NULL(matrix)
    printf("Success!\n");
}

void testMultiplication1(){
    printf("Test8: multiplication of 1x1 matrices\n");
    uint32_t rows1 = 1;
    uint32_t columns1 = 1;
    uint32_t rows2 = 1;
    uint32_t columns2 = 1;
    float** m1 = createMatrix(rows1, columns1);
    float** m2 = createMatrix(rows2, columns2);
    float** expected = createMatrix(rows1, columns2);
    m1[0][0] = (float)0.001;
    m2[0][0] = (float)0.001;
    expected[0][0] = (float)0.000001;
    float** actual = multiplyMatrices(m1, m2, rows1, columns1, rows2, columns2);
    ASSERT_TRUE(floatEq(expected[0][0], actual[0][0], 0.0001))
    printf("Success!\n");
}

void testMultiplication2(){
    printf("Test9: multiplication of 2x10 and 10x2 matrices\n");
    uint32_t rows1 = 2;
    uint32_t columns1 = 10;
    uint32_t rows2 = 10;
    uint32_t columns2 = 2;
    float** m1 = createMatrix(rows1, columns1);
    float** m2 = createMatrix(rows2, columns2);
    float** expected = createMatrix(rows1, columns1);
    for (uint32_t i = 0; i < rows1; ++i) {
        for (uint32_t j = 0; j < columns1; ++j) {
            m1[i][j] = (float)-0.5;
        }
    }
    m1[0][1] = (float) 1.0;
    m1[1][7] = (float) 0.003;
    for (uint32_t i = 0; i < rows2; ++i) {
        for (uint32_t j = 0; j < columns2; ++j) {
            m2[i][j] = (float)0.008;
        }
    }
    m2[0][0] = (float) -0.004;
    m2[3][0] = (float) 0.9;
    expected[0][0] = (float) -0.468;
    expected[0][1] = (float) -0.028;
    expected[1][0] = (float) -0.475976;
    expected[1][1] = (float) -0.035976;

    float** actual = multiplyMatrices(m1, m2, rows1, columns1, rows2, columns2);
    for (uint32_t i = 0; i < rows1; ++i) {
        for (uint32_t j = 0; j < columns2; ++j) {
            ASSERT_TRUE(floatEq(expected[i][j], actual[i][j], 0.001))
        }
    }
    printf("Success!\n");
}

void testMultiplication3(){
    printf("Test10: multiplication of 2x3 and 2x2 matrices (impossible)\n");
    uint32_t rows1 = 2;
    uint32_t columns1 = 3;
    uint32_t rows2 = 2;
    uint32_t columns2 = 2;
    float** m1 = createMatrix(rows1, columns1);
    float** m2 = createMatrix(rows2, columns2);
    for (uint32_t i = 0; i < rows1; ++i) {
        for (uint32_t j = 0; j < columns1; ++j) {
            m1[i][j] = (float)0.1;
        }
    }
    for (uint32_t i = 0; i < rows2; ++i) {
        for (uint32_t j = 0; j < columns2; ++j) {
            m2[i][j] = (float)0.1;
        }
    }
    float** actual = multiplyMatrices(m1, m2, rows1, columns1, rows2, columns2);
    ASSERT_NULL(actual)
    printf("Success!\n");
}

void testFloatToInt1(){
    printf("Test11: conversion of 0 to fixed point\n");
    float input = (float)0.0;
    int32_t actual = floatToFixed(input);
    int32_t expected = 0;
    ASSERT_EQUAL(actual, expected);
    printf("Success!\n");
}

void testFloatToInt2(){
    printf("Test12: conversion of -0.999999 to fixed point\n");
    float input = (float)-0.999999;
    int32_t actual = floatToFixed(input);
    int32_t expected = -16777199;
    ASSERT_TRUE(IntEq(expected, actual, 100));
    printf("Success!\n");
}

void testFloatToInt3(){
    printf("Test13: conversion of 1.0 to fixed point\n");
    float input = (float)1.0;
    int32_t actual = floatToFixed(input);
    int32_t expected = 16777216;
    ASSERT_EQUAL(actual, expected);
    printf("Success!\n");
}

void testFloatToInt4(){
    printf("Test14: conversion of 3.0 to fixed point (outside of declared range)\n");
    float input = (float)3.0;
    int32_t actual = floatToFixed(input);
    int32_t expected = INT_MIN;
    ASSERT_EQUAL(actual, expected);
    printf("Success!\n");
}

void testIntToFloat1(){
    printf("Test15: conversion of 2^30 to float\n");
    int32_t input = 16777216;
    float actual = fixedToFloat(input);
    float expected = (float)1.0;
    ASSERT_TRUE(floatEq(expected, actual, 0.001))
    printf("Success!\n");
}

void testIntToFloat2(){
    printf("Test16: conversion of 0 to float\n");
    int32_t input = 0;
    float actual = fixedToFloat(input);
    float expected = (float)0.0;
    ASSERT_TRUE(floatEq(expected, actual, 0.001))
    printf("Success!\n");
}

void testIntToFloat3(){
    printf("Test17: conversion of INT_MIN to float\n");
    int32_t input = INT_MIN;
    float actual = fixedToFloat(input);
    float expected = (float)-128;
    ASSERT_TRUE(floatEq(expected, actual, 0.001))
    printf("Success!\n");
}

void testIntToFloat4(){
    printf("Test18: conversion of INT_MAX to float\n");
    int32_t input = INT_MAX;
    float actual = fixedToFloat(input);
    float expected = (float)128;
    ASSERT_TRUE(floatEq(expected, actual, 0.001))
    printf("Success!\n");
}

void testIntCreation1(){
    printf("Test19: creation of 5x5 matrix\n");
    uint32_t rows = 5;
    uint32_t columns = 5;
    ASSERT_NOT_NULL(createIntMatrix(rows, columns))
    printf("Success!\n");
}

void testIntCreation2(){
    printf("Test20: creation of -1x-1 matrix\n");
    ASSERT_NULL(createIntMatrix(-1, -1))
    printf("Success!\n");
}

void testIntCreation3(){
    printf("Test21: creation of 50000x50000 matrix\n");
    uint32_t rows = 50000;
    uint32_t columns = 50000;
    ASSERT_NOT_NULL(createIntMatrix(rows, columns))
    printf("Success!\n");
}

void testLongIntCreation1(){
    printf("Test22: creation of 5x5 matrix\n");
    uint32_t rows = 5;
    uint32_t columns = 5;
    ASSERT_NOT_NULL(createLongIntMatrix(rows, columns))
    printf("Success!\n");
}

void testLongIntCreation2(){
    printf("Test23: creation of -1x-1 matrix\n");
    ASSERT_NULL(createLongIntMatrix(-1, -1))
    printf("Success!\n");
}

void testLongIntCreation3(){
    printf("Test24: creation of 10000x10000 matrix\n");
    uint32_t rows = 10000;
    uint32_t columns = 10000;
    ASSERT_NOT_NULL(createLongIntMatrix(rows, columns))
    printf("Success!\n");
}

void testIntMultiplication1(){
    printf("Test25: multiplication of 1x1 matrices\n");
    uint32_t rows1 = 1;
    uint32_t columns1 = 1;
    uint32_t rows2 = 1;
    uint32_t columns2 = 1;
    int32_t** m1 = createIntMatrix(rows1, columns1);
    int32_t** m2 = createIntMatrix(rows2, columns2);
    int32_t** expected = createIntMatrix(rows1, columns2);
    m1[0][0] = 8388608; // 0.5
    m2[0][0] = 12582912; // 0.75
    expected[0][0] = 6291456; // 0.375
    int32_t** actual = multiplyIntMatrices(m1, m2, rows1, columns1, rows2, columns2);
    ASSERT_EQUAL(expected[0][0], actual[0][0])
    printf("Success!\n");
}

void testIntMultiplication2(){
    printf("Test26: multiplication of 2x10 and 10x2 matrices\n");
    uint32_t rows1 = 2;
    uint32_t columns1 = 10;
    uint32_t rows2 = 10;
    uint32_t columns2 = 2;
    int32_t** m1 = createIntMatrix(rows1, columns1);
    int32_t** m2 = createIntMatrix(rows2, columns2);
    int32_t** expected = createIntMatrix(rows1, columns1);
    for (uint32_t i = 0; i < rows1; ++i) {
        for (uint32_t j = 0; j < columns1; ++j) {
            m1[i][j] = 1677721; // 0.1
        }
    }
    m1[0][2] = 9311354; // 0.555
    m1[1][3] = 7449083; // 0.444
    for (uint32_t i = 0; i < rows2; ++i) {
        for (uint32_t j = 0; j < columns2; ++j) {
            m2[i][j] = 2097152; // 0.125
        }
    }
    m2[0][1] = 16777216; // 1.0
    m2[4][0] = 4194304; // 0.25
    expected[0][0] = 3261071; // 0.194375
    expected[0][1] = 4519362; // 0.269375
    expected[1][0] = 3028287; // 0.1805
    expected[1][1] = 4286578; // 0.2555

    int32_t** actual = multiplyIntMatrices(m1, m2, rows1, columns1, rows2, columns2);
    for (uint32_t i = 0; i < rows1; ++i) {
        for (uint32_t j = 0; j < columns2; ++j) {
            ASSERT_TRUE(IntEq(expected[i][j], actual[i][j], 100));
        }
    }
    printf("Success!\n");
}

void testIntMultiplication3(){
    printf("Test27: multiplication of 2x3 and 2x2 matrices (impossible)\n");
    uint32_t rows1 = 2;
    uint32_t columns1 = 3;
    uint32_t rows2 = 2;
    uint32_t columns2 = 2;
    int32_t** m1 = createIntMatrix(rows1, columns1);
    int32_t** m2 = createIntMatrix(rows2, columns2);
    for (uint32_t i = 0; i < rows1; ++i) {
        for (uint32_t j = 0; j < columns1; ++j) {
            m1[i][j] = 1111111;
        }
    }
    for (uint32_t i = 0; i < rows2; ++i) {
        for (uint32_t j = 0; j < columns2; ++j) {
            m2[i][j] = 1111111;
        }
    }
    int32_t** actual = multiplyIntMatrices(m1, m2, rows1, columns1, rows2, columns2);
    ASSERT_NULL(actual)
    printf("Success!\n");
}

void mse(){
    printf("\nMean squared error of multiplication of 2x10 and 10x2 matrices:\n");
    uint32_t rows1 = 2;
    uint32_t columns1 = 10;
    uint32_t rows2 = 10;
    uint32_t columns2 = 2;
    int32_t** m1 = createIntMatrix(rows1, columns1);
    int32_t** m2 = createIntMatrix(rows2, columns2);
    for (uint32_t i = 0; i < rows1; ++i) {
        for (uint32_t j = 0; j < columns1; ++j) {
            m1[i][j] = 1677721; // 0.1
        }
    }
    m1[0][2] = 9311354; // 0.555
    m1[1][3] = 7449083; // 0.444
    for (uint32_t i = 0; i < rows2; ++i) {
        for (uint32_t j = 0; j < columns2; ++j) {
            m2[i][j] = 2097152; // 0.125
        }
    }
    m2[0][1] = 16777216; // 1.0
    m2[4][0] = 4194304; // 0.25

    float** fm1 = createMatrix(rows1, columns1);
    float** fm2 = createMatrix(rows2, columns2);
    for (uint32_t i = 0; i < rows1; ++i) {
        for (uint32_t j = 0; j < columns1; ++j) {
            fm1[i][j] = (float)0.1;
        }
    }
    fm1[0][2] = (float)0.555;
    fm1[1][3] = (float)0.444;
    for (uint32_t i = 0; i < rows2; ++i) {
        for (uint32_t j = 0; j < columns2; ++j) {
            fm2[i][j] = (float)0.125;
        }
    }
    fm2[0][1] = (float)1.0;
    fm2[4][0] = (float)0.25;

    float** fresult = multiplyMatrices(fm1, fm2, rows1, columns1, rows2, columns2);
    int32_t** result = multiplyIntMatrices(m1, m2, rows1, columns1, rows2, columns2);
    double mse = 0;

    for (uint32_t i = 0; i < rows1; ++i) {
        for (uint32_t j = 0; j < columns2; ++j) {
            mse += pow((fresult[i][j] - fixedToFloat(result[i][j])), 2);
        }
    }
    mse = mse / (double)(rows1 * columns2);
    printf("%f", mse* 100000000000000);
    printf(" * 10^-14\n");
}

void absoluteError(){
    printf("Maximum absolute error of multiplication of 2x10 and 10x2 matrices:\n");
    uint32_t rows1 = 2;
    uint32_t columns1 = 10;
    uint32_t rows2 = 10;
    uint32_t columns2 = 2;
    int32_t** m1 = createIntMatrix(rows1, columns1);
    int32_t** m2 = createIntMatrix(rows2, columns2);
    for (uint32_t i = 0; i < rows1; ++i) {
        for (uint32_t j = 0; j < columns1; ++j) {
            m1[i][j] = 1677721; // 0.1
        }
    }
    m1[0][2] = 9311354; // 0.555
    m1[1][3] = 7449083; // 0.444
    for (uint32_t i = 0; i < rows2; ++i) {
        for (uint32_t j = 0; j < columns2; ++j) {
            m2[i][j] = 2097152; // 0.125
        }
    }
    m2[0][1] = 16777216; // 1.0
    m2[4][0] = 4194304; // 0.25

    float** fm1 = createMatrix(rows1, columns1);
    float** fm2 = createMatrix(rows2, columns2);
    for (uint32_t i = 0; i < rows1; ++i) {
        for (uint32_t j = 0; j < columns1; ++j) {
            fm1[i][j] = (float)0.1;
        }
    }
    fm1[0][2] = (float)0.555;
    fm1[1][3] = (float)0.444;
    for (uint32_t i = 0; i < rows2; ++i) {
        for (uint32_t j = 0; j < columns2; ++j) {
            fm2[i][j] = (float)0.125;
        }
    }
    fm2[0][1] = (float)1.0;
    fm2[4][0] = (float)0.25;

    float** fresult = multiplyMatrices(fm1, fm2, rows1, columns1, rows2, columns2);
    int32_t** result = multiplyIntMatrices(m1, m2, rows1, columns1, rows2, columns2);
    double difference = (float) 0;
    double temp;

    for (uint32_t i = 0; i < rows1; ++i) {
        for (uint32_t j = 0; j < columns2; ++j) {
            temp = fabs(fresult[i][j] - (double)fixedToFloat(result[i][j]));
            if (difference < temp) {
                difference = temp;
            }
        }
    }
    printf("%f", difference * 10000000);
    printf(" * 10^-7\n");
}

int main() {
    // Unit-tests for floating-point matrices
    testMul1();
    testMul2();
    testCreation1();
    testCreation2();
    testCreation3();
    testFree1();
    testFree2();
    testMultiplication1();
    testMultiplication2();
    testMultiplication3();

    // Unit-tests for fixed-point matrices
    testFloatToInt1();
    testFloatToInt2();
    testFloatToInt3();
    testFloatToInt4();
    testIntToFloat1();
    testIntToFloat2();
    testIntToFloat3();
    testIntToFloat4();
    testIntCreation1();
    testIntCreation2();
    testIntCreation3();
    testLongIntCreation1();
    testLongIntCreation2();
    testLongIntCreation3();
    testIntMultiplication1();
    testIntMultiplication2();
    testIntMultiplication3();

    mse();
    absoluteError();
    return 0;
}