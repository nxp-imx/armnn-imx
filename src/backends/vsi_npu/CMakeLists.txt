#/****************************************************************************
#*
#*    Copyright (c) 2019 Vivante Corporation
#*
#*    Permission is hereby granted, free of charge, to any person obtaining a
#*    copy of this software and associated documentation files (the "Software"),
#*    to deal in the Software without restriction, including without limitation
#*    the rights to use, copy, modify, merge, publish, distribute, sublicense,
#*    and/or sell copies of the Software, and to permit persons to whom the
#*    Software is furnished to do so, subject to the following conditions:
#*
#*    The above copyright notice and this permission notice shall be included in
#*    all copies or substantial portions of the Software.
#*
#*    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#*    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#*    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#*    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#*    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#*    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
#*    DEALINGS IN THE SOFTWARE.
#*
#*****************************************************************************/

if(VSI_NPU)
    list(APPEND armnnNpuBackend_sources
        arm_nn_interpreter.cpp
        arm_nn_interpreter.hpp
        NpuBackendContext.cpp
        NpuBackendContext.hpp
        NpuBackend.cpp
        NpuBackend.hpp
        NpuBackendId.hpp
        NpuLayerSupport.cpp
        NpuLayerSupport.hpp
        NpuModelShell.cpp
        NpuModelShell.hpp
        NpuTensorAllocator.cpp
        NpuTensorAllocator.hpp
        NpuTensorHandler.cpp
        NpuTensorHandler.hpp
        NpuWorkloadFactory.cpp
        NpuWorkloadFactory.hpp
    )
    add_subdirectory(workloads)
    if(BUILD_UNIT_TESTS)
        add_subdirectory(test)
    endif()    
else()
    list(APPEND armnnNpuBackend_sources
        NpuBackendId.hpp
        NpuLayerSupport.cpp
        NpuLayerSupport.hpp
    )
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wno-old-style-cast \
                    -Wno-sign-conversion -Wno-conversion -Wno-unused-variable")

add_library(armnnNpuBackend OBJECT ${armnnNpuBackend_sources})
target_include_directories(armnnNpuBackend PRIVATE ${PROJECT_SOURCE_DIR}/src/armnn)
target_include_directories(armnnNpuBackend PRIVATE ${PROJECT_SOURCE_DIR}/src/armnnUtils)
target_include_directories(armnnNpuBackend PRIVATE ${PROJECT_SOURCE_DIR}/src/backends)
target_include_directories(armnnNpuBackend PRIVATE ${PROJECT_SOURCE_DIR}/src/backends/vsi_npu)
