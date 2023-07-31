#Makefile
cblas: main.cpp compute.cpp generate_random.cpp reread.cpp
	g++ main.cpp generate_random.cpp compute.cpp reread.cpp -o cblas -lcblas -lrefblas -lm -lgfortran -I/~/lapack/CBLAS/include  -I/~/lapack/LAPACKE/include -L/~/Downloads/lapack -DENABLE_FUNCTION -DCOMPUTE_BLAS
	./cblas

openblas: main.cpp compute.cpp generate_random.cpp reread.cpp
	g++ main.cpp generate_random.cpp compute.cpp reread.cpp -o openblas -lopenblas -lpthread -lgfortran -I/~/usr/local/OpenBLAS/include -L/usr/local/OpenBLAS/lib -DENABLE_FUNCTION -DCOMPUTE_BLAS
	./openblas

cublas: main.cpp cublas_compute.cpp generate_random.cpp reread.cpp
	nvcc main.cpp generate_random.cpp reread.cpp cublas_compute.cpp -lcublas -o cublas -DCOMPUTE_BLAS
	./cublas

gen: main.cpp generate_random.cpp
	g++ main.cpp generate_random.cpp -o gen -DGEN
	./gen

clean-w:
	-rm -rf *.o cblas openblas cublas gen

clean: 
	-rm -rf *.o cblas openblas cublas gen Data_txt/*.txt
