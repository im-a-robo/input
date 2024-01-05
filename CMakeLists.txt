cmake_minimum_required(VERSION 3.8)
project(control)
include(FetchContent)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/serial/include)

set(serial_SRCS 
    ${CMAKE_CURRENT_SOURCE_DIR}/serial/src/serial.cc 
    ${CMAKE_CURRENT_SOURCE_DIR}/serial/include/serial/serial.h
    ${CMAKE_CURRENT_SOURCE_DIR}/serial/include/serial/v8stdint.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/serial/src/impl/list_ports/list_ports_linux.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/serial/src/impl/unix.cc
    )

add_library(serial ${serial_SRCS})

# Add source for node executable (link non-ros dependencies here)
add_executable(control src/ControlNode.cpp src/ControlNode_node.cpp)
target_include_directories(control PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)
target_compile_features(control PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

target_link_libraries(control serial)

# Make ros deps a variable so they get linked to tests as well
set(dependencies
        rclcpp
        std_msgs
        sensor_msgs
        )

# Link ros dependencies
ament_target_dependencies(
        control
        ${dependencies}
)

install(TARGETS control
        DESTINATION lib/${PROJECT_NAME})

# Uncomment below to make launch files available if created
#install(
#        DIRECTORY launch config
#        DESTINATION share/${PROJECT_NAME}/
#)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
