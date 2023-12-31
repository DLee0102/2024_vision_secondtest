/**
 * @file myrobot_follow.hpp
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

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "sensor_msgs/image_encodings.hpp"
#include "cv_bridge/cv_bridge.h"
#include "geometry_msgs/msg/twist.hpp"

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <chrono>
#include <string>
#include <memory>

namespace Mydemo {
    class Myrobot_follow : public rclcpp::Node
    {
    public:
        /**
         * @brief 初始化Gazebo相机节点的订阅者、Gazebo cmd_vel节点的姿态发布者
         * 定义方块颜色参数、初始化用于检测方块颜色的字典向量
         * 
         */
        Myrobot_follow()
        : Node ("myrobot_follow_node")
        {
            subscription_ = this->create_subscription<sensor_msgs::msg::Image>("camera", 10,
                std::bind(&Myrobot_follow::topic_callback, this, std::placeholders::_1));
            publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
            this->declare_parameter("box_color", "red");

            color_dist["red"] = {cv::Scalar(0, 60, 60), cv::Scalar(6, 255, 255)};
            color_dist["blue"] = {cv::Scalar(100, 80, 46), cv::Scalar(124, 255, 255)};
            color_dist["green"] = {cv::Scalar(35, 43, 35), cv::Scalar(90, 255, 255)};
            color_dist["yellow"] = {cv::Scalar(20, 100, 100), cv::Scalar(30, 255, 255)};
        }
    private:
        /**
         * @brief 每次接收到相机发布的数据就调用该函数
         * 
         * @param msg 
         */
        void topic_callback(const sensor_msgs::msg::Image& msg);
        
        /**
         * @brief 图像预处理
         * 
         * @param img 
         * @return cv::Mat 
         */
        cv::Mat preprocessImage(cv::Mat img);

        /**
         * @brief 获取检测到的矩形的中心以及面积
         * 
         * @param img 
         * @param center_x 
         * @param center_y 
         * @param rect_size 
         * @param isFound 
         */
        void findCenter(cv::Mat& img, double& center_x, double& center_y, double& rect_size, bool& isFound);
    private:
        rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;

        std::map<std::string, std::array<cv::Scalar, 2>> color_dist;
        std::string box_color;
    };
}