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

filename1='results/cu_8000.txt'
filename2='results/open_8000.txt'

list_1=read_file_to_list(filename1)
list_2=read_file_to_list(filename2)
result_list = [i for i in range(100, len(list_2)*100+1, 100)]

plt.plot(result_list,list_1,'o-',color='k',label="cuBLAS-double")
plt.plot(result_list,list_2,'o-',color='r',label="OpenBLAS-double")
plt.title('double: OpenBLAS vs cuBLAS')
plt.xlabel("array size")#横坐标名字
plt.ylabel("compute time(s)")#纵坐标名字
plt.legend(loc = "best")#图例
plt.grid()
plt.show()
