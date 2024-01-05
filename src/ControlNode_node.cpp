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
    base_plate_angle += msg->axes[3] * spin_rate;

    // right stick up and down move mid arm up and down
    mid_arm_angle += msg->axes[4] * spin_rate;

    // left stick up and down move top arm up and down
    top_arm_angle += msg->axes[1] * spin_rate;

    std::string serial_msg = "%.2g %.2g %.2g\n", base_plate_angle, mid_arm_angle, top_arm_angle;

    if (my_serial.isOpen()) {
        std::cout << "Port opened succesfully" << std::endl;
    } else {
        std::cout << "Port failed to open" << std::endl;
    }
    my_serial.flushOutput();

    my_serial.write(serial_msg);

    my_serial.flushOutput();

    // RCLCPP_INFO(this->get_logger(), "A %.4g B %.4g C %.4g", base_plate_angle, mid_arm_angle, top_arm_angle);
}
