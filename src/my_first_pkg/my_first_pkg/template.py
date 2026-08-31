#! usr/bin/env python3


import rclpy

from rclpy.node import Node


class Mynode (Node):
    def __init__(self):
        super().__init__("my_first_node")
        self.get_logger().info("Hello ROS2! aaaa")  
        self.create_timer(1.0, self.timer_callback) 
    def timer_callback(self):
        self.get_logger().info("Hello ROS2! aaaa")


def main( args = None):    # create a node object
    rclpy.init(args=args)
    node = Mynode()  # create a node object


    rclpy.spin(node)  # keep the node alive until interrupted
    rclpy.shutdown()  # shutdown the node

if __name__ == "__main__":
    main()