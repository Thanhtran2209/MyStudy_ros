---
title: "define in C++ (preprocessor macros) and why RCLCPP_INFO is a macro"
evidence: "conversation"
evidence_type: "conversation"
capture_kind: "chat-only"
suggested_action: "create"
suggested_pages: []
attachments: []
captured_at: "2026-08-31T11-01-05Z"
captured_by: "in-session-agent"
capture_id: "cap-eb464311185c42848ba8cdde806ff9ae"
promotion_policy: "none"
promotion_decision: null
promotion_id: null
propagated_from: null
---

# `#define` in C++ — preprocessor macros

## What it is
`#define` is a **preprocessor directive**, handled by the preprocessor
*before* compilation. It performs pure **text substitution** in the
translation unit before the compiler sees the code. Macros have no type,
no scope, and are invisible to the debugger.

## Forms

### Object-like macro (constant)
```cpp
#define PI 3.14159
#define MAX_BUFFER 1024
double area = PI * r * r;   // -> 3.14159 * r * r
```

### Function-like macro (parameters)
```cpp
#define SQUARE(x) ((x) * (x))
int y = SQUARE(3 + 1);   // -> ((3 + 1) * (3 + 1)) == 16
```
Parenthesize every parameter AND the whole body. `#define SQUARE(x) x*x`
makes `SQUARE(3+1)` expand to `3+1*3+1 == 7` (operator-precedence bug).

### Include guard (common in .hpp headers)
```cpp
#ifndef MY_HEADER_H
#define MY_HEADER_H
// ... header body ...
#endif
```

## Relation to ROS 2 / rclcpp
`RCLCPP_INFO` (in `/opt/ros/jazzy/include/rclcpp/rclcpp/logging.hpp`) is a
`#define` macro. It must be a macro (not a function) because it captures
`__FILE__` / `__LINE__` / `__FUNCTION__` at the call site and can compile
out log levels conditionally. Same rationale as `assert`.

## Modern C++ guidance — prefer alternatives
| Instead of | Use |
|---|---|
| `#define PI 3.14159` | `constexpr double PI = 3.14159;` |
| `#define SQUARE(x) ((x)*(x))` | `constexpr int square(int x){ return x*x; }` |
| `#define DEBUG` | keep — conditional compilation via `#ifdef` |

Reasons to avoid macros for constants/functions: no type safety, ignore
namespaces/scope, no debugger visibility, text-substitution surprises
(multiple evaluation of arguments with side effects, precedence bugs).

Reasons `#define` is still legitimate: include guards, conditional
compilation (`#ifdef`, `#if`), and library macros needing `__FILE__` /
`__LINE__` / stringification (`#`) / token-pasting (`##`).

## Source
Answered from training data (C++ standard preprocessor semantics).
Wiki was empty (0 candidate pages) at time of capture. Triggered by user
question while inspecting rclcpp `logging.hpp:506` (`RCLCPP_INFO`).
