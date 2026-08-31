#include "rclcpp/rclcpp.hpp"


class MyFirstNode : public rclcpp::Node
{
public: 

MyFirstNode() : Node("my_first_node")
    {
        RCLCPP_INFO(this->get_logger(), "Hello, ROS2!");
    
    timer_ = this ->create_wall_timer(
        std::chrono::seconds(1),
        std::bind(&MyFirstNode::timer_callback, this)
    );
    }

private:
rclcpp::TimerBase::SharedPtr timer_;
void timer_callback()  
    {
        RCLCPP_INFO(this->get_logger(), "Hello, ROS2!");
    }


};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<MyFirstNode> ();


    rclcpp::spin(node);

    rclcpp::shutdown();

    return 0;
}