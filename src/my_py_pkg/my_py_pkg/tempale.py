import rclpy

from rclpy.node import Node


class RobotNewsStation(Node):
    def __init__(self) :
        super().__init__("robot_news_station")
        self.get_logger().info("Robot News Station is up and running!")

def main(args=None):
    rclpy.init(args=args)
    node = RobotNewsStation()
    rclpy.spin(node)
    rclpy.shutdown()


if  __name__ == "__main__":
    main()


