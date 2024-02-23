cmake_minimum_required(VERSION 3.26)
project(matrix_mul C)

set(CMAKE_C_STANDARD 11)

add_executable(matrix_mul main.c floating_point.c floating_point.h)
