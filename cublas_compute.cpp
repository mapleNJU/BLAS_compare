#include <cublas_v2.h>
#include <sys/time.h>
#include <cuda_runtime.h>
#include "operation.h"
#include <iostream>

void cublas_multiply(const std::vector<datatype> &matrix1, const std::vector<datatype> &matrix2,int num)
{
    struct timeval tc1, tc2;
    double timeusec;
    gettimeofday(&tc1, NULL);
    
    // Initialize cuBLAS
    cublasHandle_t handle;
    cublasCreate(&handle);

    // Allocate memory on the GPU
    datatype *d_A, *d_B, *d_C;
    datatype *mat1, *mat2, *result;
    cudaMalloc((void **)&d_A, num * num * sizeof(datatype));
    cudaMalloc((void **)&d_B, num * num * sizeof(datatype));
    cudaMalloc((void **)&d_C, num * num * sizeof(datatype));
    result = (datatype *)malloc(num * num * sizeof(datatype));
    mat1 = (datatype *)malloc(num * num * sizeof(datatype));
    mat2 = (datatype *)malloc(num * num * sizeof(datatype));
    std::copy(matrix1.begin(), matrix1.end(), mat1);
    std::copy(matrix2.begin(), matrix2.end(), mat2);

    // Copy input matrices from CPU to GPU
    cudaMemcpy(d_A, mat1, num * num * sizeof(datatype), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, mat2, num * num * sizeof(datatype), cudaMemcpyHostToDevice);

    const datatype alpha = 1.0;
    const datatype beta = 0.0;

    // Perform matrix multiplication using cuBLAS
    cublasSgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N,
                num, num, num, &alpha,
                d_B, num, d_A, num, &beta, d_C, num);

    // Copy the result back from GPU to the global variable
    cudaMemcpy(result, d_C, num * num * sizeof(datatype), cudaMemcpyDeviceToHost);

    // Free GPU memory and destroy cuBLAS handle
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
    free(result);
    free(mat1);
    free(mat2);
    
    cublasDestroy(handle);
    
    result=NULL;
    mat1=NULL;
    mat2=NULL;
    
    gettimeofday(&tc2, NULL);
    timeusec = (tc2.tv_sec - tc1.tv_sec) + (double)(tc2.tv_usec - tc1.tv_usec) / 1000000.0;
    times[num / gap - 1] = timeusec;
    std::cout << "compute time :" << timeusec << "s" << std::endl;
}
