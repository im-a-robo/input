#include "control/ControlNode_node.hpp"

// For _1
using namespace std::placeholders;

ControlNode::ControlNode(const rclcpp::NodeOptions& options) : Node("ControlNode", options) {

    // Pub Sub
    this->joystick_sub =
        this->create_subscription<sensor_msgs::msg::Joy>("/joy", 1, std::bind(&ControlNode::joystick_cb, this, _1));

    // Starting node log
    RCLCPP_INFO(this->get_logger(), "Control node started...");
}

void ControlNode::joystick_cb(const sensor_msgs::msg::Joy::SharedPtr msg) {

    // right stick left and right move the base plate

    // right stick up and down move mid arm up and down

    // left stick up and down move top arm up and down
}
