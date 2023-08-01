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

filename1='results/mkl_16000.txt'
#filename2='results/open_16000.txt'
#filename3='results/mkl_16000.txt'
filename4='results/mkl_8000.txt'

list_1=read_file_to_list(filename1)
#list_2=read_file_to_list(filename2)
#list_3=read_file_to_list(filename3)
list_4=read_file_to_list(filename4)
list_4=list_4+[None]*(len(list_1)-len(list_4))
result_list = [i for i in range(100, len(list_1)*100+1, 100)]

plt.plot(result_list,list_1,'o-',color='r',label="oneMKL-float")
#plt.plot(result_list,list_2,'o-',color='m',label="OpenBLAS-float")
#plt.plot(result_list,list_3,'o-',color='g',label="oneMKL-float")
plt.plot(result_list,list_4,'o-',color='g',label="oneMKL")
plt.title('oneMKL : double vs float')
plt.xlabel("array size")#横坐标名字
plt.ylabel("compute time(s)")#纵坐标名字
plt.legend(loc = "best")#图例
plt.grid()
plt.show()
