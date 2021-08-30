#
# Copyright © 2017 Arm Ltd. All rights reserved.
# Copyright 2020-2021 NXP
# SPDX-License-Identifier: MIT
#

# single place to use wildcards, so we can include
# yet unknown backend modules and corresponding common libraries
file(GLOB commonIncludes ${PROJECT_SOURCE_DIR}/src/backends/*/common.cmake)
file(GLOB backendIncludes ${PROJECT_SOURCE_DIR}/src/backends/*/backend.cmake)

# prefer to include common code first
foreach(includeFile ${commonIncludes})
    message(STATUS "Including backend common library into the build: ${includeFile}")
    include(${includeFile})
endforeach()

# now backends can depend on common code included first
foreach(includeFile ${backendIncludes})
    message(STATUS "Including backend into the build: ${includeFile}")
    include(${includeFile})
endforeach()

# parse dynamic backend sub-directories
file(GLOB dynamicBackendDirs ${PROJECT_SOURCE_DIR}/src/backends/dynamic/*)
foreach(dynamicBackendDir ${dynamicBackendDirs})
    if (EXISTS ${dynamicBackendDir} AND IS_DIRECTORY ${dynamicBackendDir})
        add_subdirectory(${dynamicBackendDir})
    endif()
endforeach()

# add VSI NPU dynamic backend
SET(vsiNpuDynamicBackendPath "${PROJECT_SOURCE_DIR}/src/backends/vsi_npu/dynamic")
if (EXISTS ${vsiNpuDynamicBackendPath} AND IS_DIRECTORY ${vsiNpuDynamicBackendPath})
    add_subdirectory(${vsiNpuDynamicBackendPath})
endif()
