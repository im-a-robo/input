#include "input/InputNode_node.hpp"

// For _1
using namespace std::placeholders;

InputNode::InputNode(const rclcpp::NodeOptions& options) : Node("InputNode", options) {
    // Pub Sub
    this->joystick_sub =
        this->create_subscription<sensor_msgs::msg::Joy>("/joy", 1, std::bind(&InputNode::joystick_cb, this, _1));
    // this->pub = this->create_publisher<sensor_msgs::msg::Joy>("/run_folder", 1);

    // Log a sample log
    RCLCPP_INFO(this->get_logger(), "Input node started...");
}

void InputNode::joystick_cb(const sensor_msgs::msg::Joy::SharedPtr msg) {


    for (int i = 0; i <= msg.get()->axes.size(); i++) {
        RCLCPP_INFO(this->get_logger(), "axis: %f, value: %f", i, msg.get()->axes.at(i));
    }

    // right stick left and right move the base plate

    // right stick up and down move mid arm up and down

    // left stick up and down move top arm up and down
}
