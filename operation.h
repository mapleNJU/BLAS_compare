#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <vector>
#include <string>

// A is m *n, B is n *p, C is m *p
#define line_M 1000
#define line_N 1000
#define line_P 1000
#define array_capacity_A line_M *line_N
#define array_capacity_B line_N *line_P
#define array_capacity_C line_M *line_P
#define datatype float
#define circle_time 5

extern int rowsA;
extern int colsA;
extern int rowsB;
extern int colsB; // colsB must be equal to rowsA
extern int num;
extern int gap;

extern double times[line_M / 100];
/*
extern datatype result[array_capacity_C];
extern datatype mat1[array_capacity_A];
extern datatype mat2[array_capacity_B];
*/
void generate_random_datatypes(int rows, int cols, datatype min_value, datatype max_value, const std::string &filename);

std::vector<datatype> read_elements_from_file(const std::string &filename, int num, int gap);

std::vector<std::vector<datatype>> matrix_multiply(const std::vector<std::vector<datatype>> &matrix1, const std::vector<std::vector<datatype>> &matrix2);

void cblas_multiply(const std::vector<datatype> &matrix1, const std::vector<datatype> &matrix2, int num);

void cublas_multiply(const std::vector<datatype> &matrix1, const std::vector<datatype> &matrix2, int num);

#endif
