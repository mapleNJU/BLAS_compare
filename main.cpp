#include <iostream>
#include <fstream>
#include "operation.h"
#include <sys/time.h>

// #define ENABLE_FUNCTION
// #define GEN
// #define COMPUTE_BLAS

int rowsA = line_M;
int colsA = line_N;
int rowsB = colsA; // rowsB must be equal to colsA
int colsB = line_P;

int num = 100; // The Matrix Multiplication Size
int gap = 100; // scale interval per matrix multiplication
/*
datatype result[array_capacity_C];
datatype mat1[array_capacity_A];
datatype mat2[array_capacity_B];
*/
double times[line_M / 100];

int main()
{

    std::string file1 = "Data_txt/write_1.txt";
    std::string file2 = "Data_txt/write_2.txt";
    std::string file_read = "Data_txt/time.txt";

#ifdef GEN
    datatype min_value = -100.0;
    datatype max_value = 100.0; // the range of random numbers
    generate_random_datatypes(rowsA, colsA, min_value, max_value, file1);
    generate_random_datatypes(rowsB, colsB, min_value, max_value, file2);
#endif

    // 读取矩阵并计算
#ifdef COMPUTE_BLAS

    while (num <= line_M)
    {
        std::cout << "num=" << num << " :" << std::endl;
        int num2 = num * num;
        std::vector<datatype> data1 = read_elements_from_file(file1, num2, gap);
        std::vector<datatype> data2 = read_elements_from_file(file2, num2, gap); // 后面调用cblas等时用这里的一维向量即可

#ifdef ENABLE_FUNCTION
        cblas_multiply(data1, data2, num);
#else
        cublas_multiply(data1, data2, num);
#endif

        num += gap;
    }

    // 写入文件
    std::ofstream outfile(file_read);
    if (!outfile)
    {
        std::cerr << "Error opening file: read.txt" << std::endl;
        return 1;
    }

    // Write the data to the file using one dimensional vectors
    for (int i = 0; i < line_M / gap; ++i)
    {
        outfile << times[i] << " ";
    }

    // Close the file
    outfile.close();

#endif
    std::cout << "complete!" << std::endl;
    return 0;
}
