## Use OpenBLAS, cuBLAS, oneMKL in singularity


OpenBLAS:

```bash
Bootstrap: docker
From: ubuntu:latest

%labels
    Author	:maple
    Version	:openblas

%files
    yourfile /opt/app/
    
%post
    apt-get update
    apt-get install -y g++ libopenblas-dev gfortran
    cd /opt/app/ && g++ main.cpp -o open -lopenblas -lgfortran -lpthread

%environment
    export PATH=/opt/app:$PATH
    
%apprun OPEN
    cd /opt/app/
    exec ./open "${@}"

%apphelp OPEN
	singularity build open.sif open.def
	singularity run --app OPEN open.sif
```

MKL:

```bash
Bootstrap: docker
From: intel/oneapi-basekit:devel-ubuntu22.04

%labels
    Author	:maple
    Version	:mkl

%post
    cd /opt/app/ && g++ main.cpp -o mkl -lmkl_rt

%environment
    export PATH=/opt/app:$PATH
    
%apprun MKL
    cd /opt/app/
    exec ./mkl "${@}"

%files
    yourfile /opt/app/
    
%apphelp MKL
	singularity build mkl.sif mkl.def
	singularity run --app MKL mkl.sif
```

cuBLAS:

```bash
Bootstrap: docker
From: ubuntu:latest

%post
    apt-get install -y wget
    
    wget https://developer.download.nvidia.com/compute/cuda/repos/wsl-ubuntu/x86_64/cuda-keyring_1.1-1_all.deb
    dpkg -i cuda-keyring_1.1-1_all.deb
    
    apt-get update
    apt-get -y install cuda

    export LD_LIBRARY_PATH=/usr/local/cuda/lib64:$LD_LIBRARY_PATH
    export PATH=/usr/local/cuda/bin:$PATH

    cd /opt/app && nvcc main.cpp -lcublas -o cublas

%environment
    export LD_LIBRARY_PATH=/usr/local/cuda/lib64:$LD_LIBRARY_PATH
    export PATH=/usr/local/cuda/bin:$PATH

%apprun CUBLAS
    # Your run script commands here
    cd /opt/app
    exec ./cublas "${@}"

%files
    yourfile /opt/app/
    
%apphelp CUBLAS
	singularity build cublas.sif cublas.def
	singularity run --app CUBLAS --nv cublas.sif
```

或：cuBLAS:

```bash
Bootstrap: docker
From: nvidia/cuda:12.2.0-runtime-ubuntu22.04

%post

%environment

%apprun CUBLAS
    # Your run script commands here
    cd /opt/app
    exec ./cublas

%files
    yourfile /opt/app/
    
%apphelp CUBLAS
    singularity build cublas.sif cublas.def
	singularity run --app CUBLAS --nv cublas.sif
```
