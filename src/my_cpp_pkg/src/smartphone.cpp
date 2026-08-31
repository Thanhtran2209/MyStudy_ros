#include "rclcpp/rclcpp.hpp"
#include <example_interfaces/msg/string.hpp>

using namespace std::chrono_literals;

class Smartphonenode  : public rclcpp::Node
{
public:
    Smartphonenode() : Node("smartphone")


    { 
        subscriber_ = this -> create_subscription<example_interfaces::msg::String>(
            "robot_news", 10, std::bind(&Smartphonenode::callback_robot_news, this, std::placeholders::_1));

        RCLCPP_INFO(this->get_logger(), "Smartphone node has been started.");

    };


private:

    void callback_robot_news(const example_interfaces::msg::String::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(), "Received news: '%s'", msg->data.c_str());
    }


rclcpp::Subscription<example_interfaces::msg::String>::SharedPtr subscriber_;
rclcpp::TimerBase::SharedPtr timer_;

} ;


int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Smartphonenode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}