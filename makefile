#Makefile
cblas: main.cpp compute.cpp generate_random.cpp reread.cpp
	g++ main.cpp generate_random.cpp compute.cpp reread.cpp -o cblas -lcblas -lrefblas -lm -lgfortran -I/~/lapack/CBLAS/include  -I/~/lapack/LAPACKE/include -L/~/Downloads/lapack -DENABLE_FUNCTION -DCOMPUTE_BLAS
	./cblas

openblas: main.cpp compute.cpp generate_random.cpp reread.cpp
	g++ main.cpp generate_random.cpp compute.cpp reread.cpp -o openblas -lopenblas -lpthread -lgfortran -L/usr/local/OpenBLAS/lib -DENABLE_FUNCTION -DCOMPUTE_BLAS
	./openblas

cublas: main.cpp cublas_compute.cpp generate_random.cpp reread.cpp
	nvcc main.cpp generate_random.cpp reread.cpp cublas_compute.cpp -lcublas -o cublas -DCOMPUTE_BLAS
	./cublas
	
mkl:main.cpp mkl_compute.cpp generate_random.cpp reread.cpp
	g++ main.cpp generate_random.cpp mkl_compute.cpp reread.cpp -o mkl -I/opt/intel/oneapi/mkl/2023.2.0/include/ -lmkl_rt -L/opt/intel/oneapi/mkl/2023.2.0/lib/intel64 -L/opt/intel/oneapi/2023.2.0/lib/intel64 -DENABLE_FUNCTION -DCOMPUTE_BLAS
	./mkl

gen: main.cpp generate_random.cpp
	g++ main.cpp generate_random.cpp -o gen -DGEN
	./gen

clean-w:
	-rm -rf *.o cblas openblas cublas gen mkl

clean: 
	-rm -rf *.o cblas openblas cublas gen mkl Data_txt/*.txt
	
mkl-install:
	wget https://registrationcenter-download.intel.com/akdlm/IRC_NAS/adb8a02c-4ee7-4882-97d6-a524150da358/l_onemkl_p_2023.2.0.49497.sh
	sudo sh ./l_onemkl_p_2023.2.0.49497.sh
