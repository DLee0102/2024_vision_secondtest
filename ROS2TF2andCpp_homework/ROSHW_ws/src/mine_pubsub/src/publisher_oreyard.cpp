#include "mine_pubsub/publisher_oreyard.hpp"

namespace Mine {
    void OreyardPublisher::pub_mineralinfo()
    {
        auto a_mineral = my_interfaces::msg::Mineral();
        this->mineral_list_ = my_interfaces::msg::MineralArray();
        int mineral_num = this->get_parameter("mineral_num").as_int();

        /* 随机生成矿石信息 */
        for (int i = 1; i <= mineral_num; i ++)
        {
            a_mineral.id = i;
            float x, y, z = 0.0f;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<float> dist_p(0.0f, 10.0f);

            /* 限制矿石位置为以原点为圆心半径为10的圆以内 */
            do {
                x = dist_p(gen);
                y = dist_p(gen);
                z = dist_p(gen);
            }
            while ( pow(x, 2) + pow(y, 2) + pow(z, 2) >= 10);
            a_mineral.position.x = x;
            a_mineral.position.y = y;
            a_mineral.position.z = z;

            /* 随机生成金矿石或银矿石 */
            std::uniform_int_distribution<int> dist_s(0, 1);
            int random_s = dist_s(gen);
            a_mineral.species = random_s == 0 ? "silver" : "gold";
            a_mineral.value = random_s == 0 ? 40.4f : 80.8f;

            this->mineral_list_.minerals.push_back(a_mineral);
        }
    }

    void OreyardPublisher::timer_callback()
    {
        RCLCPP_INFO_STREAM(this->get_logger(), "Publishing: The number of minerals is '" << this->mineral_list_.minerals.size() << "'");
        for (auto& mineral : this->mineral_list_.minerals)
        {
            RCLCPP_INFO(this->get_logger(), "mineral's ID: '%d', position: ('%f', '%f', '%f')",
                mineral.id, mineral.position.x, mineral.position.y, mineral.position.z);
        }
        std::cout << "---------------------------\n";
        mineralarray_publisher_->publish(this->mineral_list_);
    }

    void OreyardPublisher::service_digging(const std::shared_ptr<my_interfaces::srv::Digging::Request> req,
        std::shared_ptr<my_interfaces::srv::Digging::Response> resp)
    {
        RCLCPP_INFO(this->get_logger(), "Receiving a service request, the mineral's id is '%d'",
                req->id);

        /* 从矿脉中删除接收到的指定矿石的信息，并返回其位置和价值信息 */
        for (auto it = this->mineral_list_.minerals.begin(); it != this->mineral_list_.minerals.end(); it ++)
        {
            if (it->id == req->id)
            {
                resp->position = it->position;
                resp->totalvalue = it->value;
                this->mineral_list_.minerals.erase(it);
                break;
            }
        }
        
        RCLCPP_INFO(this->get_logger(), "Service processed done. The selected mineral's value is '%f'",
                resp->totalvalue);
    }

}

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Mine::OreyardPublisher>("oreyard"));
  rclcpp::shutdown();
  return 0;
}