#pragma once

#include <chrono>
#include <memory>
#include <functional>
#include <cmath>

#include "rclcpp/rclcpp.hpp"
#include "my_interfaces/msg/mineral.hpp"
#include "my_interfaces/msg/mineral_array.hpp"
#include "my_interfaces/srv/digging.hpp"
#include "geometry_msgs/msg/pose_array.hpp"
#include "geometry_msgs/msg/pose.hpp"
#include "visualization_msgs/msg/marker.hpp"
#include "visualization_msgs/msg/marker_array.hpp"


#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/transform_broadcaster.h"

namespace Mine {
    class MinerSubscriber : public rclcpp::Node
    {
    public:
        MinerSubscriber(const std::string& name) : Node(name)
        {
            /* 初始化矿工信息 */
            this->totalvalue = 0;
            this->pos_.position.x = 0.0f;
            this->pos_.position.y = 0.0f;
            this->pos_.position.z = 0.0f;

            RCLCPP_INFO(this->get_logger(), "node: %s start!", name.c_str());
            /* 创建订阅者节点 */
            mineralarray_subscriber = this->create_subscription<my_interfaces::msg::MineralArray>
                    ("oreyard", 10, std::bind(&MinerSubscriber::topic_callback, this, std::placeholders::_1));
            /* 创建client节点 */
            miner_client_ = this->create_client<my_interfaces::srv::Digging>("digging_service");

            /* 创建轨迹信息发布节点 */
            markerArray_publisher_ = this->create_publisher<visualization_msgs::msg::MarkerArray>("markerArray_pub", 10);
        }
    private:
        /**
         * @brief 订阅矿脉信息回调函数
         * 
         * @param msg 
         */
        void topic_callback(const my_interfaces::msg::MineralArray msg);

        /**
         * @brief 向server发送请求
         * 
         */
        void send_request();

        /**
         * @brief 接收server返回的结果（回调函数）
         * 
         * @param result_future 
         */
        void result_callback(rclcpp::Client<my_interfaces::srv::Digging>::SharedFuture
      result_future);
    private:
        /* 存储矿工收集的矿石的总价值 */
        float totalvalue;

        /* 存储矿工的瞬时位置信息 */
        geometry_msgs::msg::Pose pos_;
        geometry_msgs::msg::Pose temp_pos_;
        
        /* 存储矿工运动轨迹 */
        visualization_msgs::msg::MarkerArray marker_array_;
        
        rclcpp::Client<my_interfaces::srv::Digging>::SharedPtr miner_client_;

        /* 存储矿工收集的矿石信息 */
        my_interfaces::msg::MineralArray mineral_list;

        rclcpp::Subscription<my_interfaces::msg::MineralArray>::SharedPtr mineralarray_subscriber;
        rclcpp::Publisher< visualization_msgs::msg::MarkerArray>::SharedPtr markerArray_publisher_;
    };
}