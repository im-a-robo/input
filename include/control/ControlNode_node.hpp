#pragma once

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"

class ControlNode : public rclcpp::Node {
private:

    /// Subscriber for receiving joystick messages
    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joystick_sub;

    float spin_rate = 1.0f;

    float base_plate_angle = 0.0f;
    float mid_arm_angle = 0.0f;
    float top_arm_angle = 0.0f;

public:
    ControlNode(const rclcpp::NodeOptions& options);

    /// subscriber callback
    void joystick_cb(sensor_msgs::msg::Joy::SharedPtr msg);
};
