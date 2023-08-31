import cv2
import numpy as np
import math
from utiles import PreprocessImage, TargetRect
import time
import matplotlib.pyplot as plt

# 用于判断旋转方向
rotation_angle = 0
temp_rotation_angle = 0
rotation_orien = 0
rotation_num = 0

# 用于绘制旋转圆
circle_center = None
circle_r = 0

# 用于计算瞬时角速度
angle_v = 0

# 用于记录瞬时速度
angle_speedlist = []

# 利用 预测装甲板的每个角点都在圆上 以及 角点与旋转圆心构成的向量夹角为六十度（向量外积） 两个条件构建方程组进行解算
def predict_solve(a, b, circle_r_, circle_center, rotation_num, angle_v = 60):
    if rotation_num > 0:
        # 顺时针
        # y = (b + math.sqrt(3) * a) / 2
        # x = (a * y - math.sqrt(3) / 2 * math.pow(circle_r_, 2)) / b
        # y = y + circle_center[1]
        # x = x + circle_center[0]
        
        y = math.cos(angle_v) * b + math.sin(angle_v) * a
        x = (a * y - math.sin(angle_v) * math.pow(circle_r_, 2)) / b
        y = y + circle_center[1]
        x = x + circle_center[0]
    else:
        # 逆时针
        y = (b - math.sqrt(3) * a) / 2
        x = (math.sqrt(3) / 2 * math.pow(circle_r_, 2) + a * y) / b 
        y = y + circle_center[1]
        x = x + circle_center[0]
    

    
    return (x, y)
if __name__ == "__main__":
    # 打开视频文件
    video_path = 'testvideo/1red_standard.mp4'
    cap = cv2.VideoCapture(video_path)
    
    # 创建视频写入对象
    frame_rate = int(cap.get(cv2.CAP_PROP_FPS))
    frame_width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
    frame_height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
    frame_size = (frame_width // 2, frame_height // 2)  # 尺寸缩小一半
    fourcc = cv2.VideoWriter_fourcc(*'mp4v')
    writer = cv2.VideoWriter("./result.mp4", fourcc, frame_rate, frame_size)

    # 检查视频是否成功打开
    if not cap.isOpened():
        print("Error: Could not open video.")
        exit()

    while True:
        # 读取视频帧
        ret, frame = cap.read()

        # 检查是否成功读取帧
        if not ret:
            break
        
        frame = cv2.resize(frame, (int(frame.shape[1] * 0.5), int(frame.shape[0] * 0.5)))
        
        preprocess = PreprocessImage(frame, threshold_value=250, kernel_size=2)
        preprocess.findInterest()
        preprocess.getBinaryimg()
        preprocess.getOpenimg()
        preprocess.getDilateimg()
        preprocess.getCloseimg()
        
        binary_image = preprocess.getProcessedimg()
        
        # 查找轮廓
        contours, hierarchy  = cv2.findContours(binary_image, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        
        contour_image = np.copy(frame)

        # 遍历轮廓并绘制只有一个子轮廓的轮廓
        for i, contour in enumerate(contours):
            parent_index = hierarchy[0][i][3]  # 获取当前轮廓的父轮廓索引
            child_index = hierarchy[0][i][2]
            next_index = hierarchy[0][i][0]
            previous_index = hierarchy[0][i][1]
            
            contour_area = cv2.contourArea(contour)
            
            # 找到只含有一个子轮廓的轮廓，即待击打装甲板和圆心的轮廓
            if parent_index != -1 and child_index == -1 and next_index == -1 and previous_index == -1:
                # 找到圆心轮廓
                if contour_area < 100 and contour_area > 20:
                    circle_rect = TargetRect(contour)
                    
                    circle_center = circle_rect.getCenter()
                    cv2.circle(contour_image, [int(x) for x in circle_rect.getCenter()], circle_r, (0, 0, 255), thickness=1)
                    cv2.drawContours(contour_image, [circle_rect.getBox()], 0, (0, 255, 0), 6)
                # 找到待击打装甲板轮廓
                if contour_area >= 1500 and contour_area <= 2100:
                    min_rect = TargetRect(contour)
                    box = min_rect.getBox()
                    
                    if circle_center != None:
                        circle_r = int(math.sqrt(math.pow(min_rect.getRect()[0][0] - circle_center[0], 2) + pow(min_rect.getRect()[0][1] - circle_center[1], 2)))
                    
                    # 按照每秒60度的旋转角速度匀速运动预测装甲板位置
                    if circle_center != None:
                        box_predict = []
                        predict_circle_r = 0
                        for i, boxpoint in enumerate(box):
                            predict_circle_r = math.sqrt(math.pow(boxpoint[0] - circle_center[0], 2) + pow(boxpoint[1] - circle_center[1], 2))
                            predict_point = predict_solve(boxpoint[0] - circle_center[0], boxpoint[1] - circle_center[1], predict_circle_r, circle_center, rotation_num, angle_v)
                            box_predict.append(predict_point)
                        box_predict = np.int0(box_predict)
                        cv2.drawContours(contour_image, [box_predict], 0, (0, 255, 255), 2)
                        print("待击打装甲板角点预测坐标：")
                        for point in box_predict:
                            cv2.putText(contour_image, f'({point[0]},{point[1]})', tuple(point), cv2.FONT_HERSHEY_SIMPLEX, 0.3, (255, 0, 0), 1)
                            print(point)
                    
                    # 旋转方向判断利用rotation_num进行滤波，过滤掉异常值
                    if circle_center != None:
                        temp_rotation_angle = min_rect.getRect()[0]
                        temp_rotation_angle = list(temp_rotation_angle)
                        temp_rotation_angle[0] = temp_rotation_angle[0] - circle_center[0]
                        temp_rotation_angle[1] = temp_rotation_angle[1] - circle_center[1]
                        temp_rotation_angle = math.atan(temp_rotation_angle[1] / temp_rotation_angle[0])
                    
                    rotation_orien = temp_rotation_angle - rotation_angle
                    rotation_angle = temp_rotation_angle
                    
                    angle_v = rotation_orien / (1 / frame_rate)
                    angle_speedlist.append(angle_v)
                    
                    if rotation_orien > 0:
                        rotation_num += 1
                    if rotation_orien < 0:
                        rotation_num -= 1
                    if rotation_num > 0:
                        cv2.putText(contour_image, 'The direction of rotation: clockwise.', (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
                    if rotation_num < 0:
                        cv2.putText(contour_image, 'The direction of rotation: counterclockwise.', (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
                
                    cv2.drawContours(contour_image, [box], 0, (0, 255, 0), 2)
                    print("待击打装甲板角点实际坐标：")
                    # 在角点位置显示坐标信息
                    for point in box:
                        cv2.putText(contour_image, f'({point[0]},{point[1]})', tuple(point), cv2.FONT_HERSHEY_SIMPLEX, 0.3, (255, 0, 0), 1)
                        print(point)
                    
                    print("")
        
        writer.write(contour_image)
        cv2.imshow('Video Frame0', contour_image)
        
        cv2.waitKey(1)
        

    # 释放视频对象和窗口
    cap.release()
    writer.release()
    cv2.destroyAllWindows()
    
    
    # 过滤掉异常值
    filtered_angle_speedlist = []
    filtered_time_list = []
    for i, angle_speed in enumerate(angle_speedlist):
        if -3 <= angle_speed <= 3:
            filtered_angle_speedlist.append(angle_speed)

    # 绘制曲线
    plt.figure(figsize=(10, 6))
    plt.plot(filtered_angle_speedlist, color='b')
    plt.xlabel('Time')
    plt.ylabel('Angle Speed')
    plt.title('Angle Speed vs Time')
    plt.ylim(-3, 3)  # Set y-axis limit
    plt.grid()
    plt.show()
    
