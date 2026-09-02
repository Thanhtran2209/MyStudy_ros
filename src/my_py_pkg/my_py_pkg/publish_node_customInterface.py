#! /usr/bin/env python3

import rclpy
from rclpy.node import Node
from my_robot_interfaces.msg import HardwareStatus



class NumberPublisherNode(Node):
    def __init__(self):
        super().__init__("temperature_publisher_customizeInterface")
        # self.number_ = 2
        self.number_publisher_ = self.create_publisher(HardwareStatus, "temperature", 10)
        self.timer_ = self.create_timer(1.0, self.publish_number)
        self.get_logger().info("Number publisher using customize Interfaces has been started.")

    def publish_number(self):
        msg = HardwareStatus()
        msg.temperature = 34.5
        self.number_publisher_.publish(msg)


def main(args=None):
    rclpy.init(args=args)
    node = NumberPublisherNode()
    node.publish_number()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
