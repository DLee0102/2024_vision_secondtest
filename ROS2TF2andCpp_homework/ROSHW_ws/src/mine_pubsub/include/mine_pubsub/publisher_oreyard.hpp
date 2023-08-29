#pragma once

#include <chrono>
#include <memory>
#include <vector>
#include <random>
#include <cmath>

#include "rclcpp/rclcpp.hpp"
#include "my_interfaces/msg/mineral.hpp"
#include "my_interfaces/msg/mineral_array.hpp"
#include "my_interfaces/srv/digging.hpp"


namespace Mine {
    using namespace std::chrono_literals;
    class OreyardPublisher : public rclcpp::Node
    {
    public:
        OreyardPublisher(const std::string& name) : Node(name)
        {
            RCLCPP_INFO(this->get_logger(), "node: %s start!", name.c_str());
            /* 自定义矿石个数 */
            this->declare_parameter("mineral_num", 5);

            mineralarray_publisher_ = this->create_publisher<my_interfaces::msg::MineralArray>(name, 10);

            /* 绑定service回调函数 */
            auto service_callback = std::bind(&OreyardPublisher::service_digging, this, std::placeholders::_1, std::placeholders::_2);
            mineralarray_server_ = this->create_service<my_interfaces::srv::Digging>("digging_service", service_callback);

            /* 初始化矿脉信息 */
            pub_mineralinfo();
            
            /* 定时发布矿脉信息 */
            timer_= this->create_wall_timer(3000ms, std::bind(&OreyardPublisher::timer_callback, this));
        }
    private:
        /**
         * @brief 初始化矿脉信息
         * 
         */
        void pub_mineralinfo();

        /**
         * @brief 定时发布矿脉信息
         * 
         */
        void timer_callback();

        /**
         * @brief server端回调函数
         * 
         * @param req 
         * @param resp 
         */
        void service_digging(const std::shared_ptr<my_interfaces::srv::Digging::Request> req,
            std::shared_ptr<my_interfaces::srv::Digging::Response> resp);
    private:
        /* 存储矿脉所有矿石信息 */
        my_interfaces::msg::MineralArray mineral_list_;

        rclcpp::Publisher<my_interfaces::msg::MineralArray>::SharedPtr mineralarray_publisher_;
        rclcpp::Service<my_interfaces::srv::Digging>::SharedPtr mineralarray_server_;
        rclcpp::TimerBase::SharedPtr timer_;
    };
}