#Makefile
cblas: main.cpp compute.cpp generate_random.cpp reread.cpp
	g++ main.cpp generate_random.cpp compute.cpp reread.cpp -o cblas -lcblas -lrefblas -lm -lgfortran -I/~/lapack/CBLAS/include  -I/~/lapack/LAPACKE/include -L/~/Downloads/lapack -DENABLE_FUNCTION
	./cblas
openblas: main.cpp compute.cpp generate_random.cpp reread.cpp
	g++ main.cpp generate_random.cpp compute.cpp reread.cpp -o openblas -lopenblas -lpthread -lgfortran -I/~/usr/local/OpenBLAS/include -L/usr/local/OpenBLAS/lib -DENABLE_FUNCTION 
	./openblas
cublas: main.cpp cublas_compute.cpp generate_random.cpp reread.cpp
	nvcc main.cpp generate_random.cpp reread.cpp cublas_compute.cpp -lcublas -o cublas
	./cublas
gen: main.cpp generate_random.cpp
	g++ main.cpp generate_random.cpp -o gen -DGEN
	./gen
clean:
	-rm -rf *.o cblas openblas cublas Data_txt/*.txt
