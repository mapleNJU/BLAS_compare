oneMKL 安装教程：

https://www.intel.cn/content/www/cn/zh/developer/tools/oneapi/onemkl-download.html

登录官网注册并登录，填写电子邮件等必要信息后，选择linux-online Inatller（图形页面）或者linux-offline Installer（终端命令行安装）

得到两行命令，依次执行后，后面都默认就行了。注意同意使用条款。

随后cd /opt/intel/oneapi，在该目录下可以发现一个setvars.sh, 然后sudo setvars.sh intel64即可完成安装。


OpenBLAS安装：

git clone https://github.com/xianyi/OpenBLAS.git
cd OpenBLAS
make -j8
sudo make PREFIX=/usr/local/OpenBLAS install


cuBLAS直接安装CUDA即可

https://developer.nvidia.com/cuda-downloads 该网址中选择系统型号等，最好选择runfile下载，时间会比较长。随后修改环境变量 PATH 和 LD_LIBRARY_PATH. 在 ~/.bashrc 文件中写入

export PATH=$PATH:/usr/local/cuda-10.1/bin
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/cuda-10.1/lib64:/usr/lib/x86_64-linux-gnu

然后source ~/.bashrc即可
