
# 对匀速直线运动的速度参数进行卡尔曼滤波处理
# 软件学院 丁利

import json
import numpy as np
import random
from datetime import datetime
import matplotlib.pyplot as plt
import argparse

# 定义命令行输入超参数
def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '--datasource',
        type=str,
        default="read",
        required=False,
        help="generate: 重新生成数据  read: 读取已有数据")
    parser.add_argument(
        '--path',
        type=str,
        default="random_speeds100_2023-08-08_20-38-46.json",
        required=False,
        help="json文件的路径")
    return parser.parse_args()

# 生成随机数
def generateData(num_numbers=300, target_value=100, noise_range=(0.01, 0.1)):
    v_measured_dict = {}
    
    for i in range(num_numbers):
        noise = target_value * random.uniform(noise_range[0], noise_range[1])
        random_value = target_value + random.uniform(- noise, noise)
        random_value = round(random_value, 6)
        v_measured_dict[i] = random_value
        
    # 获取当前时间作为文件名的一部分
    current_time = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
    file_name = f"random_speeds{target_value}_{current_time}.json"

    # 保存生成的字典到JSON文件
    with open(file_name, 'w') as file:
        json.dump(v_measured_dict, file, indent=4)
    
    print("Generate random numbers done.")
    print("Saved to a json file.")
    print("")
    return v_measured_dict

# 读取JSON文件并加载内容到一个字典中
def readjsonData(filename):
    with open(filename, 'r') as file:
        loaded_data = json.load(file)

    print("Loading json file: ", filename)
    print("done.")
    print("")
    return loaded_data

# 卡尔曼滤波器
class KFfilter:
    def __init__(self, x0_, A_, B_, u0_, P0_, Q_, R_, H_) -> None:
        self.A = A_
        self.x0 = x0_
        self.B = B_
        self.u0 = u0_
        self.P0 = P0_
        self.Q = Q_
        self.R = R_
        self.H = H_
    
    def filter(self, measured_list):
        xba_list = []
        
        # 初始化
        xba = np.dot(self.x0, self.A) + np.dot(self.B, self.u0)
        P = np.dot(np.dot(self.A, self.P0), np.transpose(self.A)) + self.Q
        K = np.dot(P, np.transpose(self.H)) / (np.dot(np.dot(self.H, P), np.transpose(self.H)) + self.R)

        if isinstance(np.dot(K, self.H), np.ndarray):
            temp_shape = np.dot(K, self.H).shape[0]
        else:
            temp_shape = 1
        
        P = np.dot(- np.dot(K, self.H) + np.eye(temp_shape), P)
        xba_list.append(xba)
        
        # 迭代
        for x_m in measured_list:
            x = xba + np.dot(K, np.dot(self.H, x_m) - np.dot(self.H, xba))
            xba = x
            xba = np.dot(self.A, xba) + np.dot(self.B, self.u0)
            P = np.dot(np.dot(self.A, P), np.transpose(self.A)) + self.Q
            K = np.dot(P, np.transpose(self.H)) / (np.dot(np.dot(self.H, P), np.transpose(self.H)) + self.R)
            
            if isinstance(np.dot(K, self.H), np.ndarray):
                temp_shape = np.dot(K, self.H).shape[0]
            else:
                temp_shape = 1

            P = np.dot(- np.dot(K, self.H) + np.eye(temp_shape), P)
            xba_list.append(xba)
            
        return xba_list
            
    

if __name__ == '__main__':
    args = parse_args()
    target_value = 100
    if (args.datasource == "read"):
        # 读取随即生成的测量数据
        measured_dict = readjsonData(args.path)
        measured_list = []
        for data in measured_dict.values():
            measured_list.append(data)
    if (args.datasource == "generate"):
        # 生成随机数据
        measured_dict = generateData(target_value=target_value)
        measured_list = []
        for data in measured_dict.values():
            measured_list.append(data)
    
    # 使用卡尔曼滤波处理数据
    kffilter = KFfilter(x0_=np.array([0]), A_=np.array([1]), B_=np.array([0]), u0_=np.array([0]), P0_=np.array([0.5]), Q_=np.array([0.0001]), R_=np.array([0.01]), H_=np.array([1]))
    estimated_list_ = kffilter.filter(measured_list)
    
    # 叠加显示三个曲线图像：measured_list, estimated_list, 值为100的常数曲线
    plt.figure()
    plt.plot(measured_list, label="Measured")
    plt.plot(estimated_list_, label="Estimated")
    plt.plot([target_value for i in range(len(measured_list))], label="Target")
    plt.legend()
    plt.show()
    
    