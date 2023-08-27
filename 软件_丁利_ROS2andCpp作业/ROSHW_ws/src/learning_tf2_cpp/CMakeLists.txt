cmake_minimum_required(VERSION 3.8)
project(learning_tf2_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)

add_executable(hero_tf2_listener src/hero_tf2_listener.cpp)
ament_target_dependencies(
  hero_tf2_listener
  geometry_msgs
  rclcpp
  tf2
  tf2_ros
)

target_include_directories(hero_tf2_listener PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

install(TARGETS
  hero_tf2_listener
  DESTINATION lib/${PROJECT_NAME})
  
install(
  DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
