#include "rclcpp/rclcpp.hpp"
 
#include "example_interfaces/msg/int64.hpp"


class NumberCounterNode : public rclcpp::Node

{
public:

NumberCounterNode() : Node("number_counter")
{

    


}

private:

rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr  number_counter_ ;




};



int main (int argc, char **argv){


}
