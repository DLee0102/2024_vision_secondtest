# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_buffertransform_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED buffertransform_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(buffertransform_FOUND FALSE)
  elseif(NOT buffertransform_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(buffertransform_FOUND FALSE)
  endif()
  return()
endif()
set(_buffertransform_CONFIG_INCLUDED TRUE)

# output package information
if(NOT buffertransform_FIND_QUIETLY)
  message(STATUS "Found buffertransform: 0.0.0 (${buffertransform_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'buffertransform' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${buffertransform_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(buffertransform_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${buffertransform_DIR}/${_extra}")
endforeach()
