import time

import rclpy
from rclpy.node import Node
from rclpy.action import ActionServer, GoalResponse, CancelResponse
from rclpy.action.server import ServerGoalHandle
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor

from my_robot_interfaces.action import CountUntil


class CountUntilActionServer(Node):
    def __init__(self):
        super().__init__("count_until_action_server")
        self._action_server = ActionServer(
            self,
            CountUntil,
            "count_until",
            goal_callback=self.goal_callback,
            cancel_callback=self.cancel_callback,
            execute_callback=self.execute_callback,
            callback_group=ReentrantCallbackGroup(),
        )
        self.get_logger().info("Count Until action server has been started")

    def goal_callback(self, goal_request: CountUntil.Goal) -> GoalResponse:
        self.get_logger().info(
            f"Received goal request with target: {goal_request.target_number}"
        )

        if goal_request.target_number <= 0:
            self.get_logger().warn("Rejecting goal: target_number must be positive")
            return GoalResponse.REJECT

        if goal_request.delay < 0.0:
            self.get_logger().warn("Rejecting goal: delay must be >= 0")
            return GoalResponse.REJECT

        self.get_logger().info("Accepting the goal request")
        return GoalResponse.ACCEPT

    def cancel_callback(self, goal_handle: ServerGoalHandle) -> CancelResponse:
        self.get_logger().info("Received cancel request")
        return CancelResponse.ACCEPT

    def execute_callback(self, goal_handle: ServerGoalHandle):
        target_number = goal_handle.request.target_number
        delay = goal_handle.request.delay

        result = CountUntil.Result()
        feedback = CountUntil.Feedback()
        counter = 0

        self.get_logger().info(f"Executing goal, counting until {target_number}")
        for _ in range(target_number):
            if goal_handle.is_cancel_requested:
                goal_handle.canceled()
                self.get_logger().info("Goal canceled")
                result.reached_number = counter
                return result

            counter += 1
            self.get_logger().info(f"Counter: {counter}")
            feedback.current_number = counter
            goal_handle.publish_feedback(feedback)
            time.sleep(delay)

        goal_handle.succeed()
        result.reached_number = counter
        self.get_logger().info(f"Goal succeeded, reached {counter}")
        return result


def main(args=None):
    rclpy.init(args=args)
    node = CountUntilActionServer()
    executor = MultiThreadedExecutor()
    try:
        rclpy.spin(node, executor=executor)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
