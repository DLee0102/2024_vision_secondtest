#include "mine_pubsub/subscriber_miner.hpp"

namespace Mine {
    void MinerSubscriber::result_callback(rclcpp::Client<my_interfaces::srv::Digging>::SharedFuture
      result)
    {
        this->temp_pos_.position.x = result.get()->position.x;
        this->temp_pos_.position.y = result.get()->position.y;
        this->temp_pos_.position.z = result.get()->position.z;

        /* 每次创建一个新的Marker来记录位置 */
        visualization_msgs::msg::Marker marker_;
        marker_.header.frame_id = "map";
        marker_.ns = "miner path";
        marker_.id = this->get_clock()->now().nanoseconds();
        marker_.type = visualization_msgs::msg::Marker::ARROW;
        marker_.action = visualization_msgs::msg::Marker::ADD;

        /* 设置箭头形状、颜色和起始终点位置 */
        marker_.scale.x = 0.1;  
        marker_.scale.y = 0.2;  
        marker_.scale.z = 0.1;  
        marker_.color.a = 1.0;
        marker_.color.r = 1.0;
        marker_.color.g = 0.0;
        marker_.color.b = 0.0;
        marker_.points.push_back(this->pos_.position);
        marker_.points.push_back(this->temp_pos_.position);

        marker_array_.markers.push_back(marker_);

        /* 计算矿工收集的矿石的总价值 */
        this->totalvalue += result.get()->totalvalue;
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Total value: %f", this->totalvalue);
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Moved to: ('%f', '%f', '%f')",
            this->temp_pos_.position.x, this->temp_pos_.position.y, this->temp_pos_.position.z);

        /* 更新矿工实时位置 */
        this->pos_ = this->temp_pos_;
    }

    void MinerSubscriber::send_request()
    {
        /* 等待服务端上线 */
        while (!miner_client_->wait_for_service(std::chrono::seconds(1))) {
            //等待时检测rclcpp的状态
            if (!rclcpp::ok()) {
                RCLCPP_ERROR(this->get_logger(), "Interrupted while waiting for the service. Exiting.");
                return;
            }
            RCLCPP_INFO(this->get_logger(), "service not available, waiting again...");
        }

        /* 选出距离当前位置最近的矿石 */
        auto req = std::make_shared<my_interfaces::srv::Digging::Request>();
        float min_distance = 1010.0f;
        for (auto& mineral : this->mineral_list.minerals)
        {
            float distance = (float)(pow(mineral.position.x - this->pos_.position.x, 2) + pow(mineral.position.y - this->pos_.position.y, 2) + 
                pow(mineral.position.z - this->pos_.position.z, 2));
            if (distance <= min_distance)
            {
                min_distance = distance;
                req->id = mineral.id;
            }
        }
        /* 异步发送请求，不会阻塞主线程 */
        miner_client_->async_send_request(req,
            std::bind(&MinerSubscriber::result_callback, this, std::placeholders::_1));

    }

    void MinerSubscriber::topic_callback(const my_interfaces::msg::MineralArray msg)
    {
        this->mineral_list.minerals = msg.minerals;
        for (auto& mineral : this->mineral_list.minerals)
        {
            RCLCPP_INFO(this->get_logger(), "Accept a mineral: ID '%d', position ('%f', '%f', '%f')",
                mineral.id, mineral.position.x, mineral.position.y, mineral.position.z);
        }
        std::cout << "---------------------------\n";

        /* 如果矿脉中还有矿石，则继续发送请求 */
        if (this->mineral_list.minerals.size() !=0)
        {
            send_request();
        } else {
            RCLCPP_INFO(this->get_logger(), "There is no mineral in the oreyard, Stop sending request!\nThe final position is: ('%f', '%f', '%f'), total value is: '%f'",
            this->pos_.position.x, this->pos_.position.y, this->pos_.position.z, this->totalvalue);
        }
        /* 持续发布轨迹信息 */
        markerArray_publisher_->publish(this->marker_array_);
    }
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Mine::MinerSubscriber>("miner"));
  rclcpp::shutdown();
  return 0;
}