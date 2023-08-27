import cv2
import numpy as np

# 用于判断旋转方向
rotation_angle = 0
temp_rotation_angle = 0
rotation_orien = 0
rotation_num = 0

circle_center = None


# 打开视频文件
video_path = 'testvideo/1red_standard.mp4'  # 将路径替换为你的视频文件路径
cap = cv2.VideoCapture(video_path)

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
    
    # 获取图像尺寸
    height, width = frame.shape[:2]

    # 计算中心坐标
    center_x = width // 2
    center_y = height // 2

    # 定义截取的尺寸
    crop_size = 512

    # 计算截取的区域范围
    crop_x1 = center_x - crop_size // 2
    crop_x2 = center_x + crop_size // 2
    crop_y1 = center_y - crop_size // 2
    crop_y2 = center_y + crop_size // 2

    # 截取图像中心区域
    cropped_image = frame[crop_y1:crop_y2, crop_x1:crop_x2]

    # 创建一个和原图一样大小的黑色图像
    extended_image = np.zeros_like(frame)

    # 计算扩展图像中截取图像的放置位置
    x_offset = center_x - crop_size // 2
    y_offset = center_y - crop_size // 2

    # 将截取的图像放置在扩展图像的指定位置
    extended_image[y_offset:y_offset + crop_size, x_offset:x_offset + crop_size] = cropped_image



    gray_frame = cv2.cvtColor(extended_image, cv2.COLOR_BGR2GRAY)
    
    # 使用阈值进行二值化
    threshold_value = 250  # 阈值
    ret, binary_image = cv2.threshold(gray_frame, threshold_value, 255, cv2.THRESH_BINARY)
    
    # 定义结构元素（内核）
    kernel_size = 2  # 内核大小
    kernel = np.ones((kernel_size, kernel_size), np.uint8)

    # 开运算
    binary_image = cv2.morphologyEx(binary_image, cv2.MORPH_OPEN, kernel, iterations=1)
    
    # 膨胀操作
    binary_image = cv2.dilate(binary_image, kernel, iterations=3)
    
    binary_image = cv2.morphologyEx(binary_image, cv2.MORPH_CLOSE, kernel)
    
    # 查找轮廓
    contours, hierarchy  = cv2.findContours(binary_image, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    
    contour_image = np.copy(frame)
    # cv2.drawContours(contour_image, contours, -1, (0, 255, 0), 2)  # 在绿色通道上绘制轮廓
    
    # for i, contour in enumerate(contours):
    #     contour_area = cv2.contourArea(contour)
    #     if contour_area >= 500:
    #         cv2.drawContours(contour_image, contours, i, (0, 255, 0), 2)  # 在绿色通道上绘制轮廓
    
    # 遍历轮廓并绘制只有一个子轮廓的轮廓
    for i, contour in enumerate(contours):
        parent_index = hierarchy[0][i][3]  # 获取当前轮廓的父轮廓索引
        child_index = hierarchy[0][i][2]
        next_index = hierarchy[0][i][0]
        previous_index = hierarchy[0][i][1]
        
        contour_area = cv2.contourArea(contour)
        # print("(", next_index, ", ", previous_index, ", ", child_index, ", ", parent_index, ")")
        if parent_index != -1 and child_index == -1 and next_index == -1 and previous_index == -1:
            if contour_area < 100 and contour_area > 20:
                circle_rect = cv2.minAreaRect(contour)
                box_circle = cv2.boxPoints(circle_rect)
                box_circle = np.int0(box_circle)
                
                print(circle_rect[2])
                
                circle_center = circle_rect[0]
                cv2.circle(contour_image, [int(x) for x in circle_rect[0]], 200, (0, 0, 255), thickness=1)
                cv2.drawContours(contour_image, [box_circle], 0, (0, 255, 0), 6)
            if contour_area >= 1500 and contour_area <= 2100:
                min_rect = cv2.minAreaRect(contour)
                box = cv2.boxPoints(min_rect)
                box = np.int0(box)
                
                # 按照匀速运动预测装甲板位置
                min_predict = list(min_rect)
                min_predict[2] = min_predict[2] + 60.0
                box_predict = cv2.boxPoints(tuple(min_predict))
                box_predict = np.int0(box_predict)
                
                temp_rotation_angle = min_rect[2]
                rotation_orien = temp_rotation_angle - rotation_angle
                rotation_angle = temp_rotation_angle
                if rotation_orien > 0:
                    rotation_num += 1
                if rotation_orien < 0:
                    rotation_num -= 1
                if rotation_num > 0:
                    cv2.putText(contour_image, 'The direction of rotation: clockwise.', (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
                if rotation_num < 0:
                    cv2.putText(contour_image, 'The direction of rotation: counterclockwise.', (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
                
                # cv2.drawContours(contour_image, [box_predict], 0, (0, 255, 0), 2)
                cv2.drawContours(contour_image, [box], 0, (0, 255, 0), 2)
                
                print("待击打装甲板角点坐标：")
                # 在角点位置显示坐标信息
                for point in box:
                    cv2.putText(contour_image, f'({point[0]},{point[1]})', tuple(point), cv2.FONT_HERSHEY_SIMPLEX, 0.3, (255, 0, 0), 1)
                    print(point)
                
                
                print("")
    
    # 在这里可以对每一帧进行处理，比如显示、保存等
    cv2.imshow('Video Frame', contour_image)

    cv2.waitKey(1)

# 释放视频对象和窗口
cap.release()
cv2.destroyAllWindows()
