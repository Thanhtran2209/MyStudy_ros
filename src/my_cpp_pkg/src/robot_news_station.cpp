#include "rclcpp/rclcpp.hpp"
#include <example_interfaces/msg/string.hpp>

using namespace std::chrono_literals;

class RobotNewsStation : public rclcpp::Node
{
public:
    RobotNewsStation() : Node("robot_news_station")
    {
        publisher_ = this->create_publisher<example_interfaces::msg::String>("robot_news", 10);

        timer_ = this->create_wall_timer(0.5s, std::bind(&RobotNewsStation::publish_news, this));
    
        RCLCPP_INFO(this->get_logger(), "Robot News Station node has been started.");
    };


private:

    void publish_news()
    {
        auto msg = example_interfaces::msg::String();
        msg.data = "Hi I am C30 and I am here to deliver the latest news!";
        publisher_->publish(msg);
    };

rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr publisher_;
rclcpp::TimerBase::SharedPtr timer_;

} ;


int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RobotNewsStation>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}