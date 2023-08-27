#include "buffertransform/buffertransform.hpp"

void Buffertransform::on_timer()
{
    // Store frame names in variables that will be used to
    // compute transformations
    std::string fromFrameRel = target_frame_.c_str();
    std::string toFrameRel = this->toframe_;

    geometry_msgs::msg::TransformStamped t;

    // Look up for the transformation between target_frame and turtle2 frames
    // and send velocity commands for turtle2 to reach target_frame
    try {
        t = tf_buffer_->lookupTransform(
        toFrameRel, fromFrameRel,
        tf2::TimePointZero);

        RCLCPP_INFO(
            this->get_logger(),
            "Transform from '%s' to '%s':\nTranslation: (%f, %f, %f)\nRotation: (%f, %f, %f, %f)",
            toFrameRel.c_str(), fromFrameRel.c_str(),
            t.transform.translation.x, t.transform.translation.y, t.transform.translation.z,
            t.transform.rotation.x, t.transform.rotation.y, t.transform.rotation.z, t.transform.rotation.w
        );

        geometry_msgs::msg::PoseStamped transformed_point = tf_buffer_->transform(input_pos_, target_frame_);
        geometry_msgs::msg::PoseStamped transformed_back = tf_buffer_->transform(transformed_point, toFrameRel);

        RCLCPP_INFO(this->get_logger(),
            "Transformed point: (%f, %f, %f) from '%s' to '%s'",
            transformed_point.pose.position.x, transformed_point.pose.position.y, transformed_point.pose.position.z,
            input_pos_.header.frame_id.c_str(), target_frame_.c_str());
        
        RCLCPP_INFO(this->get_logger(),
            "Transformed back: (%f, %f, %f) from '%s' to '%s'",
            transformed_back.pose.position.x, transformed_back.pose.position.y, transformed_back.pose.position.z,
            target_frame_.c_str(), input_pos_.header.frame_id.c_str());

    } catch (const tf2::TransformException & ex) {
        RCLCPP_INFO(
        this->get_logger(), "Could not transform %s to %s: %s",
        toFrameRel.c_str(), fromFrameRel.c_str(), ex.what());
        return;
    }

}


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Buffertransform>(argv));
  rclcpp::shutdown();
  return 0;
}