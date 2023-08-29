import cv2
import numpy as np
import math

class PreprocessImage:
    def __init__(self, img, threshold_value, kernel_size) -> None:
        self.img_ = img.copy()
        self.hight_ = img.shape[0]
        self.width_ = img.shape[1]
        self.threshold_value_ = threshold_value
        self.kernel = np.ones((kernel_size, kernel_size), np.uint8)
    
    def findInterest(self):
        # 计算中心坐标
        center_x = self.width_ // 2
        center_y = self.hight_ // 2

        # 定义截取的尺寸
        crop_size = 512

        # 计算截取的区域范围
        crop_x1 = center_x - crop_size // 2
        crop_x2 = center_x + crop_size // 2
        crop_y1 = center_y - crop_size // 2
        crop_y2 = center_y + crop_size // 2

        # 截取图像中心区域
        cropped_image = self.img_[crop_y1:crop_y2, crop_x1:crop_x2]

        # 创建一个和原图一样大小的黑色图像
        extended_image = np.zeros_like(self.img_)

        # 计算扩展图像中截取图像的放置位置
        x_offset = center_x - crop_size // 2
        y_offset = center_y - crop_size // 2

        # 将截取的图像放置在扩展图像的指定位置
        extended_image[y_offset:y_offset + crop_size, x_offset:x_offset + crop_size] = cropped_image
        self.img_ = extended_image
        
        return extended_image
    def getBinaryimg(self):
        gray_frame = cv2.cvtColor(self.img_, cv2.COLOR_BGR2GRAY)
        # 使用阈值进行二值化
        ret, binary_image = cv2.threshold(gray_frame, self.threshold_value_, 255, cv2.THRESH_BINARY)
        self.img_ = binary_image
        return binary_image
    
    def getOpenimg(self):
        # 开运算
        binary_image = cv2.morphologyEx(self.img_, cv2.MORPH_OPEN, self.kernel, iterations=1)
        self.img_ = binary_image
        return binary_image
    
    def getDilateimg(self):
        # 膨胀操作
        binary_image = cv2.dilate(self.img_, self.kernel, iterations=3)
        self.img_ = binary_image
        return binary_image
    
    def getCloseimg(self):
        # 闭运算
        binary_image = cv2.morphologyEx(self.img_, cv2.MORPH_CLOSE, self.kernel)
        self.img_ = binary_image
        return binary_image
    
    def getProcessedimg(self):
        return self.img_

class TargetRect:
    def __init__(self, contour) -> None:
        self.rect_ = cv2.minAreaRect(contour)
        self.box_ = cv2.boxPoints(self.rect_)
        self.box_ = np.int0(self.box_)
        self.center_ = self.rect_[0]
    
    def getBox(self):
        return self.box_
    def getCenter(self):
        return self.center_
    def getRect(self):
        return self.rect_