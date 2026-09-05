# ros2_ws

A ROS 2 (Jazzy) mylearning workspace with example nodes in both Python and C++, plus a custom interfaces package.

## Packages

- **my_py_pkg** — Python (`ament_python`) nodes.
- **my_cpp_pkg** — C++ (`ament_cmake`) nodes, mirroring the Python examples.
- **my_robot_interfaces** — custom message/service definitions used by both packages.
- **my_first_pkg** — early Python examples.
- **px4_msgs**, **Micro-XRCE-DDS-Agent** — third-party dependencies for PX4/uXRCE-DDS integration.

## Custom interfaces (`my_robot_interfaces`)

**Message: `HardwareStatus`**
```
int64 version
float64 temperature
bool are_motors_ready
string debug_message
```

**Service: `ResetCounter`**
```
int64 reset_value
---
bool success
string message
```

## Nodes

Each node below exists in both `my_py_pkg` (Python) and `my_cpp_pkg` (C++) unless noted.

| Node | Description |
|---|---|
| `my_first_node` / `test_node` | Minimal example node. |
| `number_publisher` | Publishes incrementing numbers on a topic. |
| `number_counter` | Subscribes to published numbers, accumulates a running total, and hosts the `reset_counter` service (`ResetCounter.srv`) to reset the count. |
| `publish_node_custom_interface` / `temperature_publisher` | Publishes `HardwareStatus` messages. |
| `reset_counter_client` | Calls the `reset_counter` service to reset `number_counter`'s count. |
| `robot_news_station`, `smartphone` | Pub/sub example pair. |

## Build

```bash
cd ~/ros2_ws
colcon build
source install/setup.bash
```

## Run

Start the publisher and counter:
```bash
ros2 run my_py_pkg number_publisher
ros2 run my_py_pkg number_counter
```

Reset the counter via its service, either using the client node:
```bash
ros2 run my_py_pkg reset_counter_client
# or
ros2 run my_cpp_pkg reset_counter_client
```

or by calling the service directly:
```bash
ros2 service call /reset_counter my_robot_interfaces/srv/ResetCounter "{reset_value: 7}"
```

Mix and match Python/C++ nodes freely — they interoperate over standard ROS 2 topics/services.
