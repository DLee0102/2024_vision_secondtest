cmake_minimum_required(VERSION 3.8)
project(mine_pubsub)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(my_interfaces REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(visualization_msgs REQUIRED)

add_executable(oreyard src/publisher_oreyard.cpp)
ament_target_dependencies(oreyard 
  rclcpp my_interfaces std_msgs geometry_msgs tf2 tf2_ros visualization_msgs)

add_executable(miner src/subscriber_miner.cpp)
ament_target_dependencies(miner
  rclcpp my_interfaces std_msgs geometry_msgs tf2 tf2_ros visualization_msgs)

install(
  DIRECTORY launch config
  DESTINATION share/${PROJECT_NAME}
)

install(TARGETS
  oreyard
  miner
  DESTINATION lib/${PROJECT_NAME}
)

target_include_directories(oreyard PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_include_directories(miner PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

ament_package()
