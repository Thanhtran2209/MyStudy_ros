#! usr/bin/env python3


import rclpy
from rclpy.node import Node

from example_interfaces.msg import Int64 


class NumberPulisherNode (Node):
    def __init__(self):
        super().__init__("number_publisher_node")
        self.number= 10 
        self.publishers = self.create_publisher(Int64,"number",10)
        self.timer = self.create_timer(1.0, self.timer_callback)


    def publish_number(self):
        msg = Int64()
        msg.data = self.number
        self.publishers.publish(msg)
        self.get_logger().info(f"Publishing: {msg.data}")
        self.number += 1


def main( args = None):    # create a node object
    rclpy.init(args=args)
    node = NumberPublisherNode()  # create a node object


    rclpy.spin(node)  # keep the node alive until interrupted
    rclpy.shutdown()  # shutdown the node

if __name__ == "__main__":
    main()