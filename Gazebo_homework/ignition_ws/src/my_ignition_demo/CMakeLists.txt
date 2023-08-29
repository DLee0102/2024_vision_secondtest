cmake_minimum_required(VERSION 3.8)
project(my_ignition_demo)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV 4.5.0 REQUIRED)

add_executable(myrobot_follow src/myrobot_follow.cpp)
ament_target_dependencies(myrobot_follow rclcpp std_msgs sensor_msgs cv_bridge OpenCV)

install(TARGETS
  myrobot_follow
  DESTINATION lib/${PROJECT_NAME}
)

install(
  DIRECTORY launch config
  DESTINATION share/${PROJECT_NAME}
)

target_include_directories(myrobot_follow PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

ament_package()
