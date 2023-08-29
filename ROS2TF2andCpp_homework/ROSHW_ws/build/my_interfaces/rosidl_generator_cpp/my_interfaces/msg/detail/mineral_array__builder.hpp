// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from my_interfaces:msg/MineralArray.idl
// generated code does not contain a copyright notice

#ifndef MY_INTERFACES__MSG__DETAIL__MINERAL_ARRAY__BUILDER_HPP_
#define MY_INTERFACES__MSG__DETAIL__MINERAL_ARRAY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "my_interfaces/msg/detail/mineral_array__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace my_interfaces
{

namespace msg
{

namespace builder
{

class Init_MineralArray_minerals
{
public:
  explicit Init_MineralArray_minerals(::my_interfaces::msg::MineralArray & msg)
  : msg_(msg)
  {}
  ::my_interfaces::msg::MineralArray minerals(::my_interfaces::msg::MineralArray::_minerals_type arg)
  {
    msg_.minerals = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_interfaces::msg::MineralArray msg_;
};

class Init_MineralArray_header
{
public:
  Init_MineralArray_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MineralArray_minerals header(::my_interfaces::msg::MineralArray::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_MineralArray_minerals(msg_);
  }

private:
  ::my_interfaces::msg::MineralArray msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_interfaces::msg::MineralArray>()
{
  return my_interfaces::msg::builder::Init_MineralArray_header();
}

}  // namespace my_interfaces

#endif  // MY_INTERFACES__MSG__DETAIL__MINERAL_ARRAY__BUILDER_HPP_
