cmake_minimum_required(VERSION 3.8)
project(buffertransform)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)

add_executable(buffertransform src/buffertransform.cpp)
ament_target_dependencies(
  buffertransform
  geometry_msgs
  rclcpp
  tf2
  tf2_ros
  tf2_geometry_msgs
)

target_include_directories(buffertransform PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

install(TARGETS
  buffertransform
  DESTINATION lib/${PROJECT_NAME})

ament_package()
