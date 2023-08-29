/**
 * @file myrobot_follow.cpp
 * @author 丁利 (1225390750@qq.com)
 * 
 * @brief 观看视频录播时间：8月7日
 * 观看视频录播时间：8月7日
 * 观看视频录播时间：8月7日
 * 
 * @version 0.1
 * @date 2023-08-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "my_ignition_demo/myrobot_follow.hpp"

namespace Mydemo {
    cv::Mat Myrobot_follow::preprocessImage(cv::Mat img)
    {
        /* 转换为HSV格式的数据，方便识别特定颜色 */
        cv::cvtColor(img, img, cv::COLOR_BGR2HSV);
        box_color = this->get_parameter("box_color").as_string();
        
        /* 识别特定颜色范围，并将其二值化 */
        cv::inRange(img, color_dist[box_color][0], color_dist[box_color][1], img);
        return img;
    }
    void Myrobot_follow::findCenter(cv::Mat& img, double& center_x, double& center_y, double& rect_size, bool& isFound)
    {
        std::vector<std::vector<cv::Point>> contours;
        /* 提取出二值图像中的形状的轮廓 */
        cv::findContours(img.clone(), contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        if (contours.size())
        {
            isFound = true;
            /* 提取出最大的轮廓 */
            double max_area = cv::contourArea(contours[0]);
            double temp_area = 0.0;
            int max_id = 0;
            for (std::size_t i = 0; i < contours.size(); i ++)
            {
                temp_area = cv::contourArea(contours[i]);
                if (temp_area > max_area)
                {
                    max_area = temp_area;
                    max_id = i;
                }
            }
            /* 获取轮廓的外接矩形 */
            cv::RotatedRect rect = cv::minAreaRect(contours[max_id]);
            center_x = rect.center.x;
            center_y = rect.center.y;
            rect_size = (double)rect.size.area();
        } else { isFound = false; }
    }
    void Myrobot_follow::topic_callback(const sensor_msgs::msg::Image& msg)
    {
        /* 建立图像传输连接 */
        cv_bridge::CvImagePtr CVPtr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        cv::Mat img = CVPtr->image;

        /* 预处理相机传回的图像 */
        cv::Mat pre_img = preprocessImage(img.clone());
        double center_x, center_y, rect_size = 0.0;
        bool isFound;
        /* 找到检测到的特定颜色的矩形的中心 */
        findCenter(pre_img, center_x, center_y, rect_size, isFound);

        geometry_msgs::msg::Twist pub;
        /* 如果找到特定颜色矩形，则驱动小车移动使该矩形位于相机图像的中心（用矩形面积估算距离）*/
        /* 如果未找到特定颜色矩形，则驱动小车原地旋转 */
        if (isFound)
        {
            pub.angular.z = (pre_img.cols / 2 - center_x) * 0.002;
            pub.linear.x = (20000 - rect_size * 0.1) * 0.0001;
        } else {
            pub.angular.z = 0.5;
        }

        /* 发布小车姿态信息 */
        publisher_->publish(pub);

        // cv::imshow("ignition_camera", pre_img);
        
        cv::waitKey(1);


    }
}

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Mydemo::Myrobot_follow>());
    rclcpp::shutdown();
    return 0;
}