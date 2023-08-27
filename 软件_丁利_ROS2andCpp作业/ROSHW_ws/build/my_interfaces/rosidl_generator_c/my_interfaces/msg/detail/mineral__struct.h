// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from my_interfaces:msg/Mineral.idl
// generated code does not contain a copyright notice

#ifndef MY_INTERFACES__MSG__DETAIL__MINERAL__STRUCT_H_
#define MY_INTERFACES__MSG__DETAIL__MINERAL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'species'
#include "rosidl_runtime_c/string.h"
// Member 'position'
#include "geometry_msgs/msg/detail/point__struct.h"

/// Struct defined in msg/Mineral in the package my_interfaces.
typedef struct my_interfaces__msg__Mineral
{
  int32_t id;
  rosidl_runtime_c__String species;
  geometry_msgs__msg__Point position;
  double value;
} my_interfaces__msg__Mineral;

// Struct for a sequence of my_interfaces__msg__Mineral.
typedef struct my_interfaces__msg__Mineral__Sequence
{
  my_interfaces__msg__Mineral * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} my_interfaces__msg__Mineral__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MY_INTERFACES__MSG__DETAIL__MINERAL__STRUCT_H_
