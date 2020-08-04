#
# Copyright © 2020 Arm Ltd and Contributors. All rights reserved.
# SPDX-License-Identifier: MIT
#

if(BUILD_TIMELINE_DECODER)
    set(pipeCommon_sources)
    list(APPEND pipeCommon_sources
        CommandHandlerFunctor.cpp
        CommandHandlerKey.cpp
        CommandHandlerRegistry.cpp
        CommonProfilingUtils.cpp
        NetworkSockets.cpp
        PacketVersionResolver.cpp
        SwTrace.cpp)

    include_directories(${PROJECT_SOURCE_DIR}/profiling/common/include)
    include_directories(${PROJECT_SOURCE_DIR}/common/include)

    if(BUILD_UNIT_TESTS)
        include_directories(${PROJECT_SOURCE_DIR}/src/profiling
                            ${PROJECT_SOURCE_DIR}/src/armnnUtils)
        target_include_directories(UnitTests PRIVATE ${PROJECT_SOURCE_DIR}/profiling/common/include)
    endif()

    # will only build a static version of this common code
    # to simplify the build. No extra .so file to deploy to boards etc.
    add_library_ex(pipeCommon STATIC ${pipeCommon_sources})

endif()