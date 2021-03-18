#
# Copyright © 2020 Arm Ltd and Contributors. All rights reserved.
# Copyright 2021 NXP
# SPDX-License-Identifier: MIT
#

include(FindPackageHandleStandardArgs)
unset(FLATBUFFERS_FOUND)

find_path(Flatbuffers_INCLUDE_DIR
        flatbuffers/flatbuffers.h
        HINTS
            ${FLATBUFFERS_ROOT}/include
            NO_CMAKE_FIND_ROOT_PATH)

find_library(Flatbuffers_LIB
        NAMES
            libflatbuffers.a
            flatbuffers
        HINTS
            ${FLATBUFFERS_ROOT}/lib
            NO_CMAKE_FIND_ROOT_PATH)

## Set FLATBUFFERS_FOUND
find_package_handle_standard_args(Flatbuffers Flatbuffers_INCLUDE_DIR Flatbuffers_LIB)

## Set external variables for usage in CMakeLists.txt
if(FLATBUFFERS_FOUND)
    set(Flatbuffers_LIB ${Flatbuffers_LIB})
    set(Flatbuffers_INCLUDE_DIR ${Flatbuffers_INCLUDE_DIR})

    message(STATUS "Flatbuffers_LIB: ${Flatbuffers_LIB}")
    message(STATUS "Flatbuffers_INCLUDE_DIR: ${Flatbuffers_INCLUDE_DIR}")
endif()