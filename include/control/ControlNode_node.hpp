#pragma once

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "serial/serial.h"

class ControlNode : public rclcpp::Node {
private:

    serial::Serial my_serial = serial::Serial("/dev/ttyACM0", 9600, serial::Timeout::simpleTimeout(3000));

    // Rate of rotation
    float spin_rate = 1.0f;

    // Angles to be published to the servos
    float base_plate_angle = 90.0f;
    float mid_arm_angle = 90.0f;
    float top_arm_angle = 90.0f;

    /// Subscriber for receiving joystick messages
    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joystick_sub;

public:
    ControlNode(const rclcpp::NodeOptions& options);

    /// subscriber callback
    void joystick_cb(sensor_msgs::msg::Joy::SharedPtr msg);
};
