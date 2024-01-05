#include "control/ControlNode_node.hpp"

// For _1
using namespace std::placeholders;

ControlNode::ControlNode(const rclcpp::NodeOptions& options) : Node("ControlNode", options) {
    // Pub Sub
    this->joystick_sub =
        this->create_subscription<sensor_msgs::msg::Joy>("/joy", 1, std::bind(&ControlNode::joystick_cb, this, _1));

    my_serial.flushOutput();

    // Starting node log
    RCLCPP_INFO(this->get_logger(), "Control node started...");
}

void ControlNode::joystick_cb(const sensor_msgs::msg::Joy::SharedPtr msg) {
    // right stick left and right move the base plate
    base_plate_angle += -msg->axes[6] * spin_rate;

    // right stick up and down move mid arm up and down
    mid_arm_angle += msg->axes[7] * spin_rate;

    // left stick up and down move top arm up and down
    top_arm_angle += msg->axes[1] * spin_rate;
    
    RCLCPP_INFO(this->get_logger(), "A %d B %d C %d", base_plate_angle, mid_arm_angle, top_arm_angle);

    my_serial.write(std::to_string(base_plate_angle) + " " + std::to_string(mid_arm_angle) + " " + std::to_string(top_arm_angle) + "\n");

    my_serial.flushOutput();

    sleep(0.025);

}   
