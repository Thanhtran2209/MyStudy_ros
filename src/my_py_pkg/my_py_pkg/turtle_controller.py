import rclpy
from rclpy.node import Node
from turtlesim.srv import SetPen
from turtlesim.msg import Pose


X_THRESHOLD = 5.5
PEN_WIDTH = 5
RED = (255, 0, 0)
GREEN = (0, 255, 0)


class TurtleController(Node):
    def __init__(self):
        super().__init__("turtle_controller")
        self.get_logger().info("Turtle Controller is up and running!")
        self.previous_x_ = None
        self.set_pen_client_ = self.create_client(SetPen, "turtle1/set_pen")
        self.pose_subscriber_ = self.create_subscription(Pose, "turtle1/pose", self.pose_callback, 10)


    def pose_callback(self, pose: Pose):
        if self.previous_x_ is not None:
            crossed_right = pose.x >= X_THRESHOLD and self.previous_x_ < X_THRESHOLD
            crossed_left = pose.x <= X_THRESHOLD and self.previous_x_ > X_THRESHOLD

            if crossed_right:
                self.get_logger().info("Set color to red.")
                self.call_set_pen(*RED)
            elif crossed_left:
                self.get_logger().info("Set color to green.")
                self.call_set_pen(*GREEN)

        self.previous_x_ = pose.x


    def call_set_pen(self, r, g, b, width=PEN_WIDTH, off=False):
        while not self.set_pen_client_.wait_for_service(timeout_sec=1.0):
            self.get_logger().info("Waiting for service turtle1/set_pen")

        request = SetPen.Request()
        request.r = r
        request.g = g
        request.b = b
        request.width = width
        request.off = off

        future = self.set_pen_client_.call_async(request)
        future.add_done_callback(self.call_set_pen_response)


    def call_set_pen_response(self, future):
        future.result()

def main(args=None):
    rclpy.init(args=args)
    node = TurtleController()
    rclpy.spin(node)
    rclpy.shutdown()


if  __name__ == "__main__":
    main()


