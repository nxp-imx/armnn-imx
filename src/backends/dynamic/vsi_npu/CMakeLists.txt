#/****************************************************************************
#*
#*    Copyright (c) 2019 Vivante Corporation
#*    Copyright 2020 NXP
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
#*****************************************************************************

if(VSI_NPU)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wno-old-style-cast \
                     -Wno-sign-conversion -Wno-conversion -Wno-unused-variable")

   list(APPEND VsiNpuDynamicBackend_src
      NpuDynamicBackend.cpp
      )

   set(VsiNpuBackendPath ${PROJECT_SOURCE_DIR}/src/backends/vsi_npu)

   file(GLOB VsiNpuBackendBaseFiles ${VsiNpuBackendPath}/*.cpp)

   # replace static registry with dynamic
   list(APPEND VsiNpuBackendFiles ${VsiNpuBackendBaseFiles})
   list(REMOVE_ITEM VsiNpuBackendFiles ${VsiNpuBackendPath}/NpuStaticRegistry.cpp)

   add_library(Vsi_NpuAcc_backend MODULE ${VsiNpuDynamicBackend_src} ${VsiNpuBackendFiles})
   target_include_directories(Vsi_NpuAcc_backend PRIVATE ${PROJECT_SOURCE_DIR}/src/armnn)
   target_include_directories(Vsi_NpuAcc_backend PRIVATE ${PROJECT_SOURCE_DIR}/src/armnnUtils)
   target_include_directories(Vsi_NpuAcc_backend PRIVATE ${PROJECT_SOURCE_DIR}/src/backends)
   target_include_directories(Vsi_NpuAcc_backend PRIVATE ${PROJECT_SOURCE_DIR}/src/backends/vsi_npu)
   set_target_properties(Vsi_NpuAcc_backend PROPERTIES PREFIX "")
   target_link_libraries(Vsi_NpuAcc_backend armnn)
endif()
