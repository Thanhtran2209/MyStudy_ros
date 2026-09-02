cmake_minimum_required(VERSION 3.8)
project(my_cpp_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(my_robot_interfaces REQUIRED)

add_executable(my_first_node
  src/my_first_node.cpp
)
ament_target_dependencies(my_first_node
  rclcpp
)

add_executable(number_publisher
  src/number_publisher.cpp
)
ament_target_dependencies(number_publisher
  rclcpp
  example_interfaces
)

add_executable(number_counter
  src/number_counter.cpp
)
ament_target_dependencies(number_counter
  rclcpp
  example_interfaces
  my_robot_interfaces
)

add_executable(publish_node_custom_interface
  src/publish_node_customInterface.cpp
)
ament_target_dependencies(publish_node_custom_interface
  rclcpp
  my_robot_interfaces
)

install(TARGETS
  my_first_node
  number_publisher
  number_counter
  publish_node_custom_interface
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()