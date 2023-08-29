// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from my_interfaces:srv/Digging.idl
// generated code does not contain a copyright notice

#ifndef MY_INTERFACES__SRV__DETAIL__DIGGING__STRUCT_H_
#define MY_INTERFACES__SRV__DETAIL__DIGGING__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/Digging in the package my_interfaces.
typedef struct my_interfaces__srv__Digging_Request
{
  int32_t id;
} my_interfaces__srv__Digging_Request;

// Struct for a sequence of my_interfaces__srv__Digging_Request.
typedef struct my_interfaces__srv__Digging_Request__Sequence
{
  my_interfaces__srv__Digging_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} my_interfaces__srv__Digging_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'position'
#include "geometry_msgs/msg/detail/point__struct.h"

/// Struct defined in srv/Digging in the package my_interfaces.
typedef struct my_interfaces__srv__Digging_Response
{
  geometry_msgs__msg__Point position;
  double totalvalue;
} my_interfaces__srv__Digging_Response;

// Struct for a sequence of my_interfaces__srv__Digging_Response.
typedef struct my_interfaces__srv__Digging_Response__Sequence
{
  my_interfaces__srv__Digging_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} my_interfaces__srv__Digging_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MY_INTERFACES__SRV__DETAIL__DIGGING__STRUCT_H_
