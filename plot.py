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

filenamec='results/c_3000.txt'
filenameopen = 'results/open_3000.txt'
filenamecu='results/cu_3000.txt'

c_list=read_file_to_list(filenamec)
open_list = read_file_to_list(filenameopen)
cu_list=read_file_to_list(filenamecu)
result_list = [i for i in range(100, len(c_list)*100+1, 100)]


plt.plot(result_list,open_list,'o-',color = 'r',label="OpenBLAS")#s-:方形
plt.plot(result_list,cu_list,'o-',color='g',label="cuBLAS")
plt.plot(result_list,c_list,'o-',color='b',label="cBLAS")
plt.xlabel("array size")#横坐标名字
plt.ylabel("compute time(s)")#纵坐标名字
plt.legend(loc = "best")#图例
plt.grid()
plt.show()
