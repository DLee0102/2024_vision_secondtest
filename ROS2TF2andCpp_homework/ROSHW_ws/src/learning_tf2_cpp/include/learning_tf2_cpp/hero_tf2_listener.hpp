#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "geometry_msgs/msg/transform_stamped.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"
#include "tf2/exceptions.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"

using namespace std::chrono_literals;

class FrameListener : public rclcpp::Node
{
public:
    FrameListener()
    : Node("hero_tf2_frame_listener")
    {
        target_frame_ = this->declare_parameter<std::string>("target_frame", "gimbal_odom");

        tf_buffer_ =
            std::make_unique<tf2_ros::Buffer>(this->get_clock());
        tf_listener_ =
            std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

        /* 每秒调用一次回调函数 */
        timer_ = this->create_wall_timer(
            1s, std::bind(&FrameListener::on_timer, this));
    }

private:
    /**
     * @brief 定时器回调函数
     * 
     */
    void on_timer();
private:
    rclcpp::TimerBase::SharedPtr timer_{nullptr};
    std::shared_ptr<tf2_ros::TransformListener> tf_listener_{nullptr};
    std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
    std::string target_frame_;
};
