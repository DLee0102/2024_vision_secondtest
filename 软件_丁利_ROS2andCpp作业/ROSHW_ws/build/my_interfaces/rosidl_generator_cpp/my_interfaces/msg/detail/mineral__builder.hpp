// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from my_interfaces:msg/Mineral.idl
// generated code does not contain a copyright notice

#ifndef MY_INTERFACES__MSG__DETAIL__MINERAL__BUILDER_HPP_
#define MY_INTERFACES__MSG__DETAIL__MINERAL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "my_interfaces/msg/detail/mineral__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace my_interfaces
{

namespace msg
{

namespace builder
{

class Init_Mineral_value
{
public:
  explicit Init_Mineral_value(::my_interfaces::msg::Mineral & msg)
  : msg_(msg)
  {}
  ::my_interfaces::msg::Mineral value(::my_interfaces::msg::Mineral::_value_type arg)
  {
    msg_.value = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_interfaces::msg::Mineral msg_;
};

class Init_Mineral_position
{
public:
  explicit Init_Mineral_position(::my_interfaces::msg::Mineral & msg)
  : msg_(msg)
  {}
  Init_Mineral_value position(::my_interfaces::msg::Mineral::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_Mineral_value(msg_);
  }

private:
  ::my_interfaces::msg::Mineral msg_;
};

class Init_Mineral_species
{
public:
  explicit Init_Mineral_species(::my_interfaces::msg::Mineral & msg)
  : msg_(msg)
  {}
  Init_Mineral_position species(::my_interfaces::msg::Mineral::_species_type arg)
  {
    msg_.species = std::move(arg);
    return Init_Mineral_position(msg_);
  }

private:
  ::my_interfaces::msg::Mineral msg_;
};

class Init_Mineral_id
{
public:
  Init_Mineral_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Mineral_species id(::my_interfaces::msg::Mineral::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_Mineral_species(msg_);
  }

private:
  ::my_interfaces::msg::Mineral msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_interfaces::msg::Mineral>()
{
  return my_interfaces::msg::builder::Init_Mineral_id();
}

}  // namespace my_interfaces

#endif  // MY_INTERFACES__MSG__DETAIL__MINERAL__BUILDER_HPP_
