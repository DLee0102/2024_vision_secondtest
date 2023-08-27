// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from my_interfaces:srv/Digging.idl
// generated code does not contain a copyright notice

#ifndef MY_INTERFACES__SRV__DETAIL__DIGGING__BUILDER_HPP_
#define MY_INTERFACES__SRV__DETAIL__DIGGING__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "my_interfaces/srv/detail/digging__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace my_interfaces
{

namespace srv
{

namespace builder
{

class Init_Digging_Request_id
{
public:
  Init_Digging_Request_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::my_interfaces::srv::Digging_Request id(::my_interfaces::srv::Digging_Request::_id_type arg)
  {
    msg_.id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_interfaces::srv::Digging_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_interfaces::srv::Digging_Request>()
{
  return my_interfaces::srv::builder::Init_Digging_Request_id();
}

}  // namespace my_interfaces


namespace my_interfaces
{

namespace srv
{

namespace builder
{

class Init_Digging_Response_totalvalue
{
public:
  explicit Init_Digging_Response_totalvalue(::my_interfaces::srv::Digging_Response & msg)
  : msg_(msg)
  {}
  ::my_interfaces::srv::Digging_Response totalvalue(::my_interfaces::srv::Digging_Response::_totalvalue_type arg)
  {
    msg_.totalvalue = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_interfaces::srv::Digging_Response msg_;
};

class Init_Digging_Response_position
{
public:
  Init_Digging_Response_position()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Digging_Response_totalvalue position(::my_interfaces::srv::Digging_Response::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_Digging_Response_totalvalue(msg_);
  }

private:
  ::my_interfaces::srv::Digging_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_interfaces::srv::Digging_Response>()
{
  return my_interfaces::srv::builder::Init_Digging_Response_position();
}

}  // namespace my_interfaces

#endif  // MY_INTERFACES__SRV__DETAIL__DIGGING__BUILDER_HPP_
