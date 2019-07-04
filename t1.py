import csv
import os
import csv
from datetime import datetime
from matplotlib import pyplot as plt
import numpy as np
#plt.rcParams['font.sans-serif'] = ['SimHei'] # 指定默认字体
#plt.rcParams['axes.unicode_minus'] = False # 解决保存图像是负号'-'显示为方块的问题
filename='run_.-tag-test_acc.csv'

xaxis = np.arange(-10, 300)
yaxis = np.arange(-5, 100)

with open(filename,'r')as file:
    #1.创建阅读器对象
    reader=csv.reader(file)
    #2.读取文件头信息
    header_row=next(reader)

    #3.保存最高气温数据
    dates,step,hights=[],[],[]
    for row in reader:
        #current_date=datetime.strptime(row[0],"")
        dates.append(row[0])
        step.append(row[1])
        #4.将字符串转换为整型数据
        hights.append(row[2])
    #5.根据数据绘制图形

    fig=plt.figure(dpi = 128, figsize=(10,6))
    ax = plt.gca()
    #6.将列表hights传个plot()方法
    plt.plot(step[::1],hights[::1],c='red')
    #7.设置图形的格式
    plt.title('2014年4月份的温度',fontsize=24)
    plt.xlabel('',fontsize=600)
    # 8.绘制斜线日期标签
    fig.autofmt_xdate()
    plt.ylabel('华摄氏度F',fontsize=16)
    plt.tick_params(axis='both',which='major',labelsize=16)

    ax.set_xticks(xaxis[::15])
    #ax.set_yticks(yaxis[::5])
    #plt.ylim((0,100))
    plt.show()
