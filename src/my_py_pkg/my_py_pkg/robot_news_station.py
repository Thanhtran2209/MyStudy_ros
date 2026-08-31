import rclpy

from rclpy.node import Node
from example_interfaces.msg import String


class RobotNewsStation(Node):
    def __init__(self) :
        super().__init__("robot_news_station")
        self.robotname= "C30"
        self.publishers_ = self.create_publisher(String, "robot_news", 10)
        self.timer_ = self.create_timer(0.5, self.publish_news)

        self.get_logger().info("Robot News Station is up and running!")


          
    def publish_news(self):
        msg = String()
        msg.data = "Hi I am " + self.robotname + " and I am here to deliver the latest news!"
        self.publishers_.publish(msg)



def main(args=None):
    rclpy.init(args=args)
    node = RobotNewsStation()
    rclpy.spin(node)
    rclpy.shutdown()


if  __name__ == "__main__":
    main()


