#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"

#include <functional>
#include <my_robot_interfaces/srv/reset_counter.hpp>


using ReserCounter = my_robot_interfaces::srv::ResetCounter;

class NumberCounterNode : public rclcpp::Node
{
public:
    NumberCounterNode() : Node("number_counter")
    {
        RCLCPP_INFO(this->get_logger(), "Number counter has been started");
        number_subscriber_ = this->create_subscription<example_interfaces::msg::Int64>(
            "number", 10,
            std::bind(&NumberCounterNode::callbackNumber, this, std::placeholders::_1));

        reset_counter_service_ = this->create_service<ReserCounter>("reset_counter", std::bind(&NumberCounterNode::callbackResetCounter, 
            this, std::placeholders::_1, std::placeholders::_2));

    }

private:

    void callbackResetCounter(const std::shared_ptr<ReserCounter::Request> request, 
        std::shared_ptr<ReserCounter::Response> response)
    {

        if (request->reset_value < 0) {
            response->success = false;
            RCLCPP_INFO(this->get_logger(), "Cannot reset counter to a negative value.");
        } else if (request->reset_value > counter_) {
            response->success = false;
            RCLCPP_INFO(this->get_logger(), "Cannot reset counter to a value greater than the current counter value.");
        } else {
            counter_ = request->reset_value;
            response->success = true;
            response->message = "Success";
            RCLCPP_INFO(this->get_logger(), "Reset counter to %ld", counter_);
        }
          
    }



    

    void callbackNumber(const example_interfaces::msg::Int64::SharedPtr msg)
    {
        counter_ += msg->data;
        RCLCPP_INFO(this->get_logger(), "Counter: %ld", counter_);
    }

    int64_t counter_ = 0;
    rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr number_subscriber_;

    rclcpp::Service<ReserCounter>::SharedPtr reset_counter_service_;

};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberCounterNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
