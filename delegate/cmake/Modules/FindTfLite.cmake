#
# Copyright © 2020 Arm Ltd and Contributors. All rights reserved.
# Copyright 2021 NXP
# SPDX-License-Identifier: MIT
#

include(FindPackageHandleStandardArgs)
unset(TFLITE_FOUND)

find_path(TfLite_INCLUDE_DIR
        NAMES
            tensorflow/lite
        HINTS
            ${TFLITE_INCLUDE_DIR} # path to TensorFlow repository root
        NO_CMAKE_FIND_ROOT_PATH)

find_library(TfLite_LIB
        NAMES
            "libtensorflow_lite_all.so"
            "libtensorflowlite.so"
            "libtensorflow-lite.so"
            "libtensorflow-lite.a"
        HINTS
            ${TFLITE_LIB_DIR} # path to prebuilt TF Lite library
        NO_CMAKE_FIND_ROOT_PATH)

find_path(TfLite_Schema_INCLUDE_PATH
            schema_generated.h
        HINTS
            ${TF_LITE_SCHEMA_INCLUDE_PATH} # path to TF Lite schema
        NO_CMAKE_FIND_ROOT_PATH)

## Set TFLITE_FOUND
find_package_handle_standard_args(TfLite TfLite_INCLUDE_DIR TfLite_LIB TfLite_Schema_INCLUDE_PATH)

## Set external variables for usage in CMakeLists.txt
if(TFLITE_FOUND)
    set(TfLite_LIB ${TfLite_LIB})
    set(TfLite_INCLUDE_DIR ${TfLite_INCLUDE_DIR})
    set(TfLite_Schema_INCLUDE_PATH ${TfLite_Schema_INCLUDE_PATH})

    message(STATUS "TfLite_LIB: ${TfLite_LIB}")
    message(STATUS "TfLite_INCLUDE_DIR: ${TfLite_INCLUDE_DIR}")
    message(STATUS "TfLite_Schema_INCLUDE_PATH: ${TfLite_Schema_INCLUDE_PATH}")
endif()

## TIM-VX is a VSI-proprietary lib used by TF Lite in ovxlib delegate if available
find_library(TimVX_LIB
    NAMES
        "libtim-vx.so"
        "libtim-vx-static.a"
    HINTS
        ${TIMVX_LIB_DIR})

if (TimVX_LIB)
    set(TIMVX_LIB ${TimVX_LIB})
    message(STATUS "TimVX_LIB: ${TimVX_LIB}")
else()
    message(STATUS "TimVX_LIB not found.")
endif()
