#include <vector>
#include "operation.h"
#include <time.h>
#include <cstring>
#include <sys/time.h>
#include <iostream>

extern "C"
{
#include "mkl.h"
}

void cblas_multiply(const std::vector<datatype> &matrix1, const std::vector<datatype> &matrix2, int num)
{ // 传入A,B矩阵及它们对应的行数
    double average_time = 0.0;
    for (int i = 0; i < circle_time; i++)
    {
        struct timeval tc1, tc2;
        double timeusec;
        gettimeofday(&tc1, NULL);

        const datatype alpha = 1;
        const datatype beta = 0; // using in cblas_dgemm

        datatype *mat1, *mat2, *result;
        mat1 = (datatype *)mkl_malloc(num * num * sizeof(datatype),64);
        mat2 = (datatype *)mkl_malloc(num * num * sizeof(datatype),64);
        result = (datatype *)mkl_malloc(num * num * sizeof(datatype),64);

        std::copy(matrix1.begin(), matrix1.end(), mat1);
        std::copy(matrix2.begin(), matrix2.end(), mat2);

        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, num, num, num, alpha, mat1, num, mat2, num, beta, result, num); // 用cblas计算矩阵乘法

        mkl_free(mat1);
        mkl_free(mat2);
        mkl_free(result);

        gettimeofday(&tc2, NULL);
        timeusec = (tc2.tv_sec - tc1.tv_sec) + (double)(tc2.tv_usec - tc1.tv_usec) / 1000000.0;
        average_time += timeusec / circle_time;

        std::cout << "compute time :" << timeusec << "s" << std::endl;
    }
    times[num / gap - 1] = average_time;
    std::cout << "average time :" << average_time << "s" << std::endl;
}
