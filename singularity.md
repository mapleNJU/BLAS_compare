## Use OpenBLAS, cuBLAS, oneMKL in singularity

 
OpenBLAS:

```
Bootstrap: docker
From: ubuntu:latest

%labels
    Author	:maple
    Version	:openblas

%post
    sed -i 's/archive.ubuntu.com/mirrors.huaweicloud.com/g' /etc/apt/sources.list
    sed -i 's/security.ubuntu.com/mirrors.huaweicloud.com/g' /etc/apt/sources.list
    apt-get update
    apt-get install -y g++
    apt-get install -y make
    apt-get install -y git
    apt-get install -y libopenblas-dev gfortran
    cd /opt/app/ && g++ main.cpp compute.cpp generate_random.cpp reread.cpp -o open -lopenblas -lgfortran -lpthread -DENABLE_FUNCTION -DCOMPUTE_BLAS

%environment
    export PATH=/opt/app:$PATH
    
%apprun OPEN
    cd /opt/app/
    exec ./open


%files
    ./app/*.cpp /opt/app/
    ./app/operation.h /opt/app/
    ./Data_txt/*.txt /opt/Data_txt
```

MKL:

```
Bootstrap: docker
From: intel/oneapi-basekit:devel-ubuntu22.04

%labels
    Author	:maple
    Version	:mkl

%post
    cd /opt/app/ && g++ main.cpp mkl_compute.cpp generate_random.cpp reread.cpp -o mkl -lmkl_rt -DENABLE_FUNCTION -DCOMPUTE_BLAS

%environment
    export PATH=/opt/app:$PATH
    
%apprun MKL
    cd /opt/app/
    exec ./mkl


%files
    ./app/*.cpp /opt/app/
    ./app/operation.h /opt/app/
    ./Data_txt/*.txt /opt/Data_txt
```

cuBLAS:

```
Bootstrap: docker
From: ubuntu:latest

%post
    # Update the package manager and install necessary dependencies
    sed -i 's/archive.ubuntu.com/mirrors.huaweicloud.com/g' /etc/apt/sources.list
    sed -i 's/security.ubuntu.com/mirrors.huaweicloud.com/g' /etc/apt/sources.list
    apt-get update
    apt-get install -y wget

    wget https://developer.download.nvidia.com/compute/cuda/repos/wsl-ubuntu/x86_64/cuda-keyring_1.1-1_all.deb
    dpkg -i cuda-keyring_1.1-1_all.deb
    apt-get update
    apt-get -y install cuda

    export LD_LIBRARY_PATH=/usr/local/cuda/lib64:$LD_LIBRARY_PATH
    export PATH=/usr/local/cuda/bin:$PATH

    cd /opt/app && nvcc main.cpp generate_random.cpp reread.cpp cublas_compute.cpp -lcublas -o cublas -DCOMPUTE_BLAS

%environment
    export LD_LIBRARY_PATH=/usr/local/cuda/lib64:$LD_LIBRARY_PATH
    export PATH=/usr/local/cuda/bin:$PATH


%apprun CUBLAS
    # Your run script commands here
    cd /opt/app
    exec ./cublas

%files
    ./app/*.cpp /opt/app/
    ./app/operation.h /opt/app/
    ./Data_txt/*.txt /opt/Data_txt
```

