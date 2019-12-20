#/****************************************************************************
#*
#*    Copyright 2019 NXP
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

include(CheckIncludeFiles)

target_include_directories(inferenceTest PRIVATE ../../src/armnnUtils)
target_include_directories(inferenceTest PRIVATE ../../src/backends)
target_include_directories(inferenceTest PRIVATE ../../third-party/stb)

if(BUILD_CAFFE_PARSER)
    macro(CaffeParserTest testName sources)
        add_executable_ex(${testName} ${sources})
        target_include_directories(${testName} PRIVATE ../../src/armnnUtils)
        target_include_directories(${testName} PRIVATE ../../src/backends)
        target_include_directories(${testName} PRIVATE ../../)
        set_target_properties(${testName} PROPERTIES COMPILE_FLAGS "${CAFFE_PARSER_TEST_ADDITIONAL_COMPILE_FLAGS}")

        target_link_libraries(${testName} inferenceTest)
        target_link_libraries(${testName} armnnCaffeParser)
        target_link_libraries(${testName} armnn)
        target_link_libraries(${testName} ${CMAKE_THREAD_LIBS_INIT})
        if(OPENCL_LIBRARIES)
            target_link_libraries(${testName} ${OPENCL_LIBRARIES})
        endif()
        if(VSI_NPU_LIBRARIES)
            target_link_libraries(${testName} ${VSI_NPU_LIBRARIES})
        endif()
        target_link_libraries(${testName}
            ${Boost_SYSTEM_LIBRARY}
            ${Boost_FILESYSTEM_LIBRARY}
            ${Boost_PROGRAM_OPTIONS_LIBRARY})
        addDllCopyCommands(${testName})
    endmacro()

    set(VSI-CaffeAlexNet-Armnn_sources
        CaffeAlexNet-Armnn.cpp
        ../CaffePreprocessor.hpp
        ../CaffePreprocessor.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    CaffeParserTest(VSI-CaffeAlexNet-Armnn "${VSI-CaffeAlexNet-Armnn_sources}")

    set(VSI-CaffeInception_BN-Armnn_sources
        CaffeInception_BN-Armnn.cpp
        ../CaffePreprocessor.hpp
        ../CaffePreprocessor.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    CaffeParserTest(VSI-CaffeInception_BN-Armnn "${VSI-CaffeInception_BN-Armnn_sources}")

    set(VSI-CaffeInceptionV3-Armnn_sources
        CaffeInceptionV3-Armnn.cpp
        ../CaffePreprocessor.hpp
        ../CaffePreprocessor.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    CaffeParserTest(VSI-CaffeInceptionV3-Armnn "${VSI-CaffeInceptionV3-Armnn_sources}")

    set(VSI-CaffeMobilenetV2-Armnn_sources
        CaffeMobilenetV2-Armnn.cpp
        ../CaffePreprocessor.hpp
        ../CaffePreprocessor.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    CaffeParserTest(VSI-CaffeMobilenetV2-Armnn "${VSI-CaffeMobilenetV2-Armnn_sources}")

    set(VSI-CaffeResNet-Armnn_sources
        CaffeResNet-Armnn.cpp
        ../CaffePreprocessor.hpp
        ../CaffePreprocessor.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    CaffeParserTest(VSI-CaffeResNet-Armnn "${VSI-CaffeResNet-Armnn_sources}")

    set(VSI-CaffeSqueezeNet1_0-Armnn_sources
        CaffeSqueezeNet1_0-Armnn.cpp
        ../CaffePreprocessor.hpp
        ../CaffePreprocessor.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    CaffeParserTest(VSI-CaffeSqueezeNet1_0-Armnn "${VSI-CaffeSqueezeNet1_0-Armnn_sources}")

    set(VSI-CaffeSqueezeNet1_1-Armnn_sources
        CaffeSqueezeNet1_1-Armnn.cpp
        ../CaffePreprocessor.hpp
        ../CaffePreprocessor.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    CaffeParserTest(VSI-CaffeSqueezeNet1_1-Armnn "${VSI-CaffeSqueezeNet1_1-Armnn_sources}")

    set(VSI-CaffeVGG-Armnn_sources
        CaffeVGG-Armnn.cpp
        ../CaffePreprocessor.hpp
        ../CaffePreprocessor.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    CaffeParserTest(VSI-CaffeVGG-Armnn "${VSI-CaffeVGG-Armnn_sources}")

    set(VSI-CaffeYolo-Armnn_sources
        CaffeYolo-Armnn.cpp
        ../YoloDatabase.hpp
        ../YoloDatabase.cpp
        ../YoloInferenceTest.hpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    CaffeParserTest(VSI-CaffeYolo-Armnn "${VSI-CaffeYolo-Armnn_sources}")
endif()

if(BUILD_TF_PARSER)
    macro(TfParserTest testName sources)
        add_executable_ex(${testName} ${sources})
        target_include_directories(${testName} PRIVATE ../../src/armnnUtils)
        target_include_directories(${testName} PRIVATE ../../src/backends)
        target_include_directories(${testName} PRIVATE ../../)

        target_link_libraries(${testName} inferenceTest)
        target_link_libraries(${testName} armnnTfParser)
        target_link_libraries(${testName} armnn)
        target_link_libraries(${testName} ${CMAKE_THREAD_LIBS_INIT})
        if(OPENCL_LIBRARIES)
            target_link_libraries(${testName} ${OPENCL_LIBRARIES})
        endif()
        if(VSI_NPU_LIBRARIES)
            target_link_libraries(${testName} ${VSI_NPU_LIBRARIES})
        endif()
        target_link_libraries(${testName}
            ${Boost_SYSTEM_LIBRARY}
            ${Boost_FILESYSTEM_LIBRARY}
            ${Boost_PROGRAM_OPTIONS_LIBRARY})
        addDllCopyCommands(${testName})
    endmacro()

    set(VSI-TfMobileNet-Armnn_sources
        TfMobileNet-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfParserTest(VSI-TfMobileNet-Armnn "${VSI-TfMobileNet-Armnn_sources}")

    set(VSI-TfInceptionV3-Armnn_sources
        TfInceptionV3-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfParserTest(VSI-TfInceptionV3-Armnn "${VSI-TfInceptionV3-Armnn_sources}")

endif()

if (BUILD_TF_LITE_PARSER)
    macro(TfLiteParserTest testName sources)
        add_executable_ex(${testName} ${sources})
        target_include_directories(${testName} PRIVATE ../../src/armnnUtils)
        target_include_directories(${testName} PRIVATE ../../src/backends)
        target_include_directories(${testName} PRIVATE ../../)

        target_link_libraries(${testName} inferenceTest)
        target_link_libraries(${testName} armnnTfLiteParser)
        target_link_libraries(${testName} armnn)
        target_link_libraries(${testName} ${CMAKE_THREAD_LIBS_INIT})
        if(VSI_NPU_LIBRARIES)
            target_link_libraries(${testName} ${VSI_NPU_LIBRARIES})
        endif()
        if(OPENCL_LIBRARIES)
            target_link_libraries(${testName} ${OPENCL_LIBRARIES})
        endif()
        target_link_libraries(${testName}
            ${Boost_SYSTEM_LIBRARY}
            ${Boost_FILESYSTEM_LIBRARY}
            ${Boost_PROGRAM_OPTIONS_LIBRARY})
        addDllCopyCommands(${testName})
    endmacro()

	set(VSI-TfLiteMnasNet-Armnn_sources
        TfLiteMnasNet-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(VSI-TfLiteMnasNet-Armnn "${VSI-TfLiteMnasNet-Armnn_sources}")

    set(VSI-TfLiteMobileNetSsd-Armnn_sources
        TfLiteMobileNetSsd-Armnn.cpp
        ../MobileNetSsdDatabase.hpp
        ../MobileNetSsdInferenceTest.hpp
        ../ObjectDetectionCommon.hpp)
    TfLiteParserTest(VSI-TfLiteMobileNetSsd-Armnn "${VSI-TfLiteMobileNetSsd-Armnn_sources}")

    set(VSI-TfLiteDensenetFloat-Armnn_sources
        TfLiteDensenetFloat-Armnn.cpp
        ../MobileNetSsdDatabase.hpp
        ../MobileNetSsdInferenceTest.hpp
        ../ObjectDetectionCommon.hpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(VSI-TfLiteDensenetFloat-Armnn "${VSI-TfLiteDensenetFloat-Armnn_sources}")

    set(VSI-TfLiteSqueezenetFloat-Armnn_sources
        TfLiteSqueezenetFloat-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(VSI-TfLiteSqueezenetFloat-Armnn "${VSI-TfLiteSqueezenetFloat-Armnn_sources}")

    set(VSI-TfLiteInceptionV3Quantized-Armnn_sources
        TfLiteInceptionV3Quantized-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(VSI-TfLiteInceptionV3Quantized-Armnn "${VSI-TfLiteInceptionV3Quantized-Armnn_sources}")

    set(VSI-TfLiteInceptionV3Float-Armnn_sources
        TfLiteInceptionV3Float-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(VSI-TfLiteInceptionV3Float-Armnn "${VSI-TfLiteInceptionV3Float-Armnn_sources}")

    set(VSI-TfLiteInceptionV4Quantized-Armnn_sources
        TfLiteInceptionV4Quantized-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(VSI-TfLiteInceptionV4Quantized-Armnn "${VSI-TfLiteInceptionV4Quantized-Armnn_sources}")

    set(VSI-TfLiteInceptionV4Float-Armnn_sources
        TfLiteInceptionV4Float-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(VSI-TfLiteInceptionV4Float-Armnn "${VSI-TfLiteInceptionV4Float-Armnn_sources}")

    set(VSI-TfLiteResnetV2Float-Armnn_sources
        TfLiteResnetV2Float-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(VSI-TfLiteResnetV2Float-Armnn "${VSI-TfLiteResnetV2Float-Armnn_sources}")

    set(VSI-TfLiteMobilenetV1Float-Armnn_sources
        TfLiteMobilenetV1Float-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(VSI-TfLiteMobilenetV1Float-Armnn "${VSI-TfLiteMobilenetV1Float-Armnn_sources}")

    set(VSI-TfLiteInceptionV1Quantized-Armnn_sources
        TfLiteInceptionV1Quantized-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(VSI-TfLiteInceptionV1Quantized-Armnn "${VSI-TfLiteInceptionV1Quantized-Armnn_sources}")

    set(VSI-TfLiteMobilenetV1Quantized-Armnn_sources
        TfLiteMobilenetV1Quantized-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(VSI-TfLiteMobilenetV1Quantized-Armnn "${VSI-TfLiteMobilenetV1Quantized-Armnn_sources}")

    set(VSI-TfLiteMobilenetV2Quantized-Armnn_sources
        TfLiteMobilenetV2Quantized-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(VSI-TfLiteMobilenetV2Quantized-Armnn "${VSI-TfLiteMobilenetV2Quantized-Armnn_sources}")

    set(VSI-TfLiteInceptionResnetV2Float-Armnn_sources
        TfLiteInceptionResnetV2Float-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(VSI-TfLiteInceptionResnetV2Float-Armnn "${VSI-TfLiteInceptionResnetV2Float-Armnn_sources}")
endif()
