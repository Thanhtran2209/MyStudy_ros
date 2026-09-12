#include <memory>
#include <thread>
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "my_robot_interfaces/action/count_until.hpp"

class CountUntilActionServer : public rclcpp::Node
{
public:
  // Short aliases for the action type and its goal handle type
  using CountUntil = my_robot_interfaces::action::CountUntil;
  using GoalHandleCountUntil = rclcpp_action::ServerGoalHandle<CountUntil>;
  using namespace std::placeholders;  


  // explicit: forbid implicit conversion from NodeOptions to CountUntilActionServer.
  // NodeOptions has a default value, so the node can still be built with make_shared<>().
  explicit CountUntilActionServer() : Node("count_until_action_server")
  {


    count_until_server_ = rclcpp_action::create_server<CountUntil>(
      this,
      "count_until",
      std::bind(&CountUntilActionServer::goalCallback, this, _1, _2),
      std::bind(&CountUntilActionServer::cancelCallback, this, _1),
      std::bind(&CountUntilActionServer::executeCallback, this, _1));

    RCLCPP_INFO(this->get_logger(), "Count Until action server has been started");
  }

private:
  rclcpp_action::Server<CountUntil>::SharedPtr count_until_server_;

  // Validate the goal before accepting it (equivalent to goal_callback in Python)
  rclcpp_action::GoalResponse goalCallback(
    const rclcpp_action::GoalUUID & uuid,
    std::shared_ptr<const CountUntil::Goal> goal)
  {
    (void)uuid;  // uuid unused; cast to void to silence the "unused parameter" warning
    RCLCPP_INFO(this->get_logger(),
      "Received goal request with target: %ld", goal->target_number);

    // target_number must be positive
    if (goal->target_number <= 0) {
      RCLCPP_WARN(this->get_logger(), "Rejecting goal: target_number must be positive");
      return rclcpp_action::GoalResponse::REJECT;
    }

    // delay must not be negative
    if (goal->delay < 0.0) {
      RCLCPP_WARN(this->get_logger(), "Rejecting goal: delay must be >= 0");
      return rclcpp_action::GoalResponse::REJECT;
    }

    RCLCPP_INFO(this->get_logger(), "Accepting the goal request");
    // ACCEPT_AND_EXECUTE: accept the goal and allow it to start immediately
    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
  }

  // Receive a cancel request for a goal (equivalent to cancel_callback in Python)
  rclcpp_action::CancelResponse cancelCallback(
    const std::shared_ptr<GoalHandleCountUntil> goal_handle)
  {
    (void)goal_handle;
    RCLCPP_INFO(this->get_logger(), "Received cancel request");
    return rclcpp_action::CancelResponse::ACCEPT;
  }

  // Goal accepted -> run execute() on a separate thread so the executor is
  // not blocked (execute() sleeps and runs for a long time).
  void executeCallback(const std::shared_ptr<GoalHandleCountUntil> goal_handle)
  {
    std::thread{std::bind(&CountUntilActionServer::execute, this, goal_handle)}.detach();
  }

  // Main counting loop (equivalent to execute_callback in Python)
  void execute(const std::shared_ptr<GoalHandleCountUntil> goal_handle)
  {
    // Read the request data from the goal
    const auto goal = goal_handle->get_goal();
    const int64_t target_number = goal->target_number;
    const double delay = goal->delay;

    auto result = std::make_shared<CountUntil::Result>();
    auto feedback = std::make_shared<CountUntil::Feedback>();
    int64_t counter = 0;

    RCLCPP_INFO(this->get_logger(), "Executing goal, counting until %ld", target_number);
    for (int64_t i = 0; i < target_number; i++) {
      // If the client requested a cancel -> stop and return the partial result
      if (goal_handle->is_canceling()) {
        result->reached_number = counter;
        goal_handle->canceled(result);
        RCLCPP_INFO(this->get_logger(), "Goal canceled");
        return;
      }

      counter++;
      RCLCPP_INFO(this->get_logger(), "Counter: %ld", counter);

      // Publish feedback: the value currently reached
      feedback->current_number = counter;
      goal_handle->publish_feedback(feedback);

      // Wait 'delay' seconds (double -> chrono::duration)
      std::this_thread::sleep_for(std::chrono::duration<double>(delay));
    }

    // Counting done -> report success with the final result
    result->reached_number = counter;
    goal_handle->succeed(result);
    RCLCPP_INFO(this->get_logger(), "Goal succeeded, reached %ld", counter);
  }
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<CountUntilActionServer>();
  // MultiThreadedExecutor: lets the cancel callback run while execute() is sleeping
  rclcpp::executors::MultiThreadedExecutor executor;
  executor.add_node(node);
  executor.spin();
  rclcpp::shutdown();
  return 0;
}
