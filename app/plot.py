import matplotlib.pyplot as plt
#折线图

def read_file_to_list(filename):
    result_list = []
    with open(filename, 'r') as file:
        content = file.read()
        numbers = content.split()  # Split based on whitespace characters
        for num_str in numbers:
            result_list.append(float(num_str))
    return result_list

filename1='Datas/open-i7.txt'
filename2='Datas/mkl-i7.txt'
filename3='Datas/cu-i7.txt'
filename4='Datas/open-i9.txt'
filename5='Datas/mkl-i9.txt'
filename6='Datas/cu-i9.txt'
filename7='Datas/cblas.txt'
filename8='Datas/sin-open.txt'
filename9='Datas/sin-mkl.txt'
filename0='Datas/sin-cu.txt'

list_1=read_file_to_list(filename1)
list_2=read_file_to_list(filename2)
list_3=read_file_to_list(filename3)
list_4=read_file_to_list(filename4)
list_5=read_file_to_list(filename5)
list_6=read_file_to_list(filename6)
list_7=read_file_to_list(filename7)
list_7=list_7+[None]*(len(list_4)-len(list_7))
list_8=read_file_to_list(filename8)
list_9=read_file_to_list(filename9)
list_0=read_file_to_list(filename0)
x_list = [i*4 for i in range(100, len(list_6)*100+1, 100)]

re_list_1=[]
re_list_2=[]
re_list_3=[]
#re_list_4=[]
for i in range(int(len(list_3)/4)):
    re_list_1.append(list_1[i*4+3])
    re_list_2.append(list_2[i*4+3])
    re_list_3.append(list_3[i*4+3])
    

plt.plot(x_list,re_list_1,'s:',color='r',label="i7-openBLAS")
plt.plot(x_list,re_list_2,'s:',color='b',label="i7-oneMKL")
#plt.plot(x_list,re_list_3,'s:',color='g',label="1660s-cuBLAS")
plt.plot(x_list,list_4,'o-',color='r',label="i9-openBLAS")
plt.plot(x_list,list_5,'o-',color='b',label="i9-oneMKL")
plt.plot(x_list,list_6,'o-',color='g',label="2080Ti-cuBLAS")
plt.plot(x_list,list_7,'o-',color='m',label="cBLAS")
plt.plot(x_list,list_8,'*-.',color='r',label="singularity-openBLAS")
plt.plot(x_list,list_9,'*-.',color='b',label="singularity-oneMKL")
plt.plot(x_list,list_0,'*-.',color='g',label="singularity-cuBLAS")
plt.title('BLAS compute time compare')
plt.xlabel("array size")#横坐标名字
plt.ylabel("compute time(s)")#纵坐标名字
plt.legend(loc = "best")#图例
plt.grid()
plt.show()
