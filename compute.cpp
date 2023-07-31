#include <vector>
#include "operation.h"
#include <time.h>
#include <cstring>
#include <sys/time.h>
#include <iostream>

extern "C"
{
#include "cblas.h"
}

void cblas_multiply(const std::vector<datatype> &matrix1, const std::vector<datatype> &matrix2, int num)
{ // 传入A,B矩阵及它们对应的行数
    double average_time = 0.0;
    for (int i = 0; i < circle_time; i++)
    {
        struct timeval tc1, tc2;
        double timeusec;
        gettimeofday(&tc1, NULL);

        const enum CBLAS_ORDER Order = CblasRowMajor;
        const enum CBLAS_TRANSPOSE TransA = CblasNoTrans;
        const enum CBLAS_TRANSPOSE TransB = CblasNoTrans;
        const datatype alpha = 1;
        const datatype beta = 0; // using in cblas_dgemm

        datatype *mat1, *mat2, *result;
        mat1 = (datatype *)malloc(num * num * sizeof(datatype));
        mat2 = (datatype *)malloc(num * num * sizeof(datatype));
        result = (datatype *)malloc(num * num * sizeof(datatype));

        std::copy(matrix1.begin(), matrix1.end(), mat1);
        std::copy(matrix2.begin(), matrix2.end(), mat2);

        cblas_sgemm(Order, TransA, TransB, num, num, num, alpha, mat1, num, mat2, num, beta, result, num); // 用cblas计算矩阵乘法

        free(mat1);
        free(mat2);
        free(result);

        mat1 = NULL;
        mat2 = NULL;
        result = NULL;

        gettimeofday(&tc2, NULL);
        timeusec = (tc2.tv_sec - tc1.tv_sec) + (double)(tc2.tv_usec - tc1.tv_usec) / 1000000.0;
        average_time += timeusec / circle_time;

        std::cout << "compute time :" << timeusec << "s" << std::endl;
    }
    times[num / gap - 1] = average_time;
    std::cout << "average time :" << average_time << "s" << std::endl;
}
