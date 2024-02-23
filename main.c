#include "floating_point.c"

void testMul1(){
    printf("Test1: are matrices ax3 and 3xb multiplicable\n");
    ASSERT_TRUE(isMultiplicable(3, 3))
    printf("Success!\n");
}

void testMul2(){
    printf("Test2: are matrices ax5 and 4xb multiplicable\n");
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
    printf("Test4: creation of -1x-1 matrix\n");
    ASSERT_NULL(createMatrix(-1, -1))
    printf("Success!\n");
}

void testCreation3(){
    printf("Test5: creation of 10^5x10^5 matrix\n");
    uint32_t rows = 100000;
    uint32_t columns = 100000;
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
    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < columns1; ++j) {
            m1[i][j] = (float)-0.5;
        }
    }
    m1[0][1] = (float) 1.0;
    m1[1][7] = (float) 0.003;
    for (int i = 0; i < rows2; ++i) {
        for (int j = 0; j < columns2; ++j) {
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
    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < columns2; ++j) {
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
    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < columns1; ++j) {
            m1[i][j] = (float)0.1;
        }
    }
    for (int i = 0; i < rows2; ++i) {
        for (int j = 0; j < columns2; ++j) {
            m2[i][j] = (float)0.1;
        }
    }
    float** actual = multiplyMatrices(m1, m2, rows1, columns1, rows2, columns2);
    ASSERT_NULL(actual)
    printf("Success!\n");
}

int main() {

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


    return 0;
}
