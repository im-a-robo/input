#pragma once

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"

class InputNode : public rclcpp::Node {
private:
    // rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub;

    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joystick_sub;

public:
    InputNode(const rclcpp::NodeOptions& options);

    /// subscriber callback
    void joystick_cb(sensor_msgs::msg::Joy::SharedPtr msg);
};
