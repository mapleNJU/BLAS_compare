## cBLAS vs OpenBLAS vs cuBLAS 的矩阵乘法运行时间比较程序

**Attention:请自行安装lapacke, OpenBLAS, cuBLAS等，并根据实际情况修改makefile中的参数**

### 功能

##### 实验环境：
* CPU:Intel i7-10700(16) @ 4.800GHz
* GPU:NVIDIA GeForce GTX 1660 SUPER
* 内存：16GB

##### 功能：
实现了在相同条件下cBLAS, OpenBLAS, cuBLAS在大规模矩阵相乘时的计算时间对比。在float数据类型下，两个16000\*16000的矩阵相乘时，OpenBLAS的计算时间约15.6s, cuBLAS的计算时间约2.3s, 提升了约85%。而在GPU不擅长的double型数据处理中，两个9000\*9000的矩阵相乘时，OpenBLAS的计算时间约为6.0s, cuBLAS的计算时间约为9.3s(如果有好的显卡则运行时间会比OpenBLAS快)。由于cBLAS为单线程处理，在float型3000\*3000的矩阵相乘时运算时间已经达到了11.6s, 此时OpenBLAS运算时间为0.09s,cuBLAS运算时间为0.04s, 所以后续没有测试cBLAS.

### 文件

.
├── compute.cpp

├── cublas_compute.cpp

├── Data_txt

├── generate_random.cpp

├── main.cpp

├── makefile

├── operation.h

├── plot.py

├── README.md

└── reread.cpp

**compute.cpp** : 用cBLAS方法或者OpenBLAS方法计算矩阵乘法
**cublas_compute.cpp** : 用cuBLAS方法计算矩阵乘法
**Data_txt** : 存放结果目录
**generate_random.cpp** : 生成随机数并存放至Data_txt目录下
**main.cpp** : 主文件
**makefile** : makefile文件，命令如下：
* make clean : 清除所有可执行目标文件和txt文件
* make clean-w : 清除所有可执行目标文件
* make cblas : 用cBLAS方法进行计算
* make openblas : 用OpenBLAS方法进行计算
* make cublas : 用cuBLAS方法进行计算
* make gen : 生成随机数文件
  
**operation.h** : 头文件
**plot.py** : 画折线图
**reread.cpp** : 在计算过程中从文件中读取新数据的函数

### 可以进行修改的参数：

##### operation.h : 
   * line_M : 矩阵乘法中A矩阵的行数和C矩阵的行数，但在该程序中不用考虑，因为这是方阵。修改line_M即可修改矩阵乘法的最大规模，如设置为10000即表示从开始计算到10000*10000为止
	* line_N : 矩阵乘法中A矩阵的列数和B矩阵的行数，但在该程序中用不到
	* line_P : 矩阵乘法中B矩阵的列数和C矩阵的列数，但在该程序中用不到
	* datatype : 数据的类型，目前试过float和double两种类型
		* 特别注意：在修改了datatype之后，要在compute.cpp中和cublas_compute.cpp中修改矩阵乘法的参数，具体为cblas_xgemm/cublasXgemm : 其中X=d表示double型，X=s表示float型
	* circle_time : 每个大小的矩阵乘法的计算次数
  
##### main.cpp :
* num : 每次矩阵乘法的规模，也可以设置开始时的矩阵乘法规模
* gap : 计算完该次矩阵乘法后，下次计算规模增加多少，如100表示100\*100->200\*200
* 请注意修改了这两个参数之后，一定要修改main.cpp和operation.h中double times[]的大小，把该值修改为一共计算的规模数
* file_read : 存储的文件名

### 实验结果示例：

##### 16000\*16000-float-cBLAS vs cuBLAS vs OpenBLAS:

![16000 compare](https://github.com/mapleNJU/BLAS_compare/blob/master/results/16000_compare.png)

##### 8000\*8000-double-cuBLAS vs OpenBLAS:

![8000 compare](https://github.com/mapleNJU/BLAS_compare/blob/master/results/16000_compare.png)

##### cuBLAS:double vs float:

![cuBLAS_compare](https://github.com/mapleNJU/BLAS_compare/blob/master/results/cuBLAS.png)

##### OpenBLAS:double vs float:

![OpenBLAS_compare](https://github.com/mapleNJU/BLAS_compare/blob/master/results/openBLAS.png)
