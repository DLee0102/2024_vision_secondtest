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
            this->totalvalue = 0;
            this->pos_.position.x = 0.0f;
            this->pos_.position.y = 0.0f;
            this->pos_.position.z = 0.0f;


            RCLCPP_INFO(this->get_logger(), "node: %s start!", name.c_str());
            mineralarray_subscriber = this->create_subscription<my_interfaces::msg::MineralArray>
                    ("oreyard", 10, std::bind(&MinerSubscriber::topic_callback, this, std::placeholders::_1));
            miner_client_ = this->create_client<my_interfaces::srv::Digging>("digging_service");

            markerArray_publisher_ = this->create_publisher<visualization_msgs::msg::MarkerArray>("markerArray_pub", 10);
        }
    private:
        void topic_callback(const my_interfaces::msg::MineralArray msg); 
        void send_request();
        void result_callback(rclcpp::Client<my_interfaces::srv::Digging>::SharedFuture
      result_future);
    private:
        float totalvalue;
        geometry_msgs::msg::Pose pos_;
        geometry_msgs::msg::Pose temp_pos_;
        
        visualization_msgs::msg::MarkerArray marker_array_;
        

        rclcpp::Client<my_interfaces::srv::Digging>::SharedPtr miner_client_;
        my_interfaces::msg::MineralArray mineral_list;
        rclcpp::Subscription<my_interfaces::msg::MineralArray>::SharedPtr mineralarray_subscriber;
        rclcpp::Publisher< visualization_msgs::msg::MarkerArray>::SharedPtr markerArray_publisher_;
    };
}