#include "learning_tf2_cpp/hero_tf2_listener.hpp"


void FrameListener::on_timer()
{
    // Store frame names in variables that will be used to
    // compute transformations
    std::string fromFrameRel = target_frame_.c_str();
    std::string toFrameRel = "camera_optical_link";

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
  rclcpp::spin(std::make_shared<FrameListener>());
  rclcpp::shutdown();
  return 0;
}