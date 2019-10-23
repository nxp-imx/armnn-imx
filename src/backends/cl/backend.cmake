#
# Copyright © 2017 Arm Ltd. All rights reserved.
# SPDX-License-Identifier: MIT
#

add_subdirectory(${PROJECT_SOURCE_DIR}/src/backends/cl)
list(APPEND armnnLibraries armnnClBackend)

if(ARMCOMPUTECL)
    message("CL backend is enabled")
    list(APPEND armnnLibraries armnnClBackendWorkloads)
    list(APPEND armnnUnitTestLibraries armnnClBackendUnitTests)
else()
    message("CL backend is disabled")
endif()
