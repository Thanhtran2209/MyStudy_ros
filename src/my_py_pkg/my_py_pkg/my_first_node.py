#! /usr/bin/env python3 

import rclpy
from rclpy.node import Node 

class MyCustomNode(Node):

    def __init__(self):
        super().__init__("my_custom_node")
        self.timer = self.create_timer(1.0, self.timer_callback)
        self.counter = 0 

    def timer_callback(self):
        self.get_logger().info("Hello ROS2 "+ str(self.counter))
        self.counter += 1
   
def main(args=None):
        rclpy.init(args=args)
        node = MyCustomNode()
        rclpy.spin(node)
        node.destroy_node()
        rclpy.shutdown()

if  __name__ == "__main__":
    main()