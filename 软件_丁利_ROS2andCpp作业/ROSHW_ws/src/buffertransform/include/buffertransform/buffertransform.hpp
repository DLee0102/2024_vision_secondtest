#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "geometry_msgs/msg/transform_stamped.hpp"
#include "rclcpp/rclcpp.hpp"
#include "tf2/exceptions.h"
#include "tf2_ros/buffer.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"

using namespace std::chrono_literals;

class Buffertransform : public rclcpp::Node
{
public:
    Buffertransform(char* argv[])
    : Node ("buffertranform_node")
    {
        input_pos_.pose.position.x = std::stof(argv[1]);
        input_pos_.pose.position.y = std::stof(argv[2]);
        input_pos_.pose.position.z = std::stof(argv[3]);

        toframe_ = argv[4];
        input_pos_.header.frame_id = toframe_;
        fromframe_ = argv[5];

        // Declare and acquire `target_frame` parameter
        target_frame_ = this->declare_parameter<std::string>("target_frame", fromframe_);

        tf_buffer_ =
            std::make_unique<tf2_ros::Buffer>(this->get_clock());
        tf_listener_ =
            std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

        // Call on_timer function every second
        timer_ = this->create_wall_timer(
            1s, std::bind(&Buffertransform::on_timer, this));
    }
private:
    void on_timer();
private:
    geometry_msgs::msg::PoseStamped input_pos_;
    std::string toframe_;
    std::string fromframe_;

    rclcpp::TimerBase::SharedPtr timer_{nullptr};
    std::shared_ptr<tf2_ros::TransformListener> tf_listener_{nullptr};
    std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
    std::string target_frame_;

};