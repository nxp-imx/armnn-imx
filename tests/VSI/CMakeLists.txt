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

# UnitTests
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

    set(CaffeAlexNet-Armnn-VSI_sources
        CaffeAlexNet-Armnn.cpp
        ../CaffePreprocessor.hpp
        ../CaffePreprocessor.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    CaffeParserTest(CaffeAlexNet-Armnn-VSI "${CaffeAlexNet-Armnn-VSI_sources}")

    set(CaffeInception_BN-Armnn-VSI_sources
        CaffeInception_BN-Armnn.cpp
        ../CaffePreprocessor.hpp
        ../CaffePreprocessor.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    CaffeParserTest(CaffeInception_BN-Armnn-VSI "${CaffeInception_BN-Armnn-VSI_sources}")

    set(CaffeInceptionV3-Armnn-VSI_sources
        CaffeInceptionV3-Armnn.cpp
        ../CaffePreprocessor.hpp
        ../CaffePreprocessor.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    CaffeParserTest(CaffeInceptionV3-Armnn-VSI "${CaffeInceptionV3-Armnn-VSI_sources}")

    set(CaffeInceptionV4-Armnn-VSI_sources
        CaffeInceptionV4-Armnn.cpp
        ../CaffePreprocessor.hpp
        ../CaffePreprocessor.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    CaffeParserTest(CaffeInceptionV4-Armnn-VSI "${CaffeInceptionV4-Armnn-VSI_sources}")

    set(CaffeMobilenetV1-Armnn-VSI_sources
        CaffeMobilenetV1-Armnn.cpp
        ../CaffePreprocessor.hpp
        ../CaffePreprocessor.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    CaffeParserTest(CaffeMobilenetV1-Armnn-VSI "${CaffeMobilenetV1-Armnn-VSI_sources}")

    set(CaffeMobilenetV2-Armnn-VSI_sources
        CaffeMobilenetV2-Armnn.cpp
        ../CaffePreprocessor.hpp
        ../CaffePreprocessor.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    CaffeParserTest(CaffeMobilenetV2-Armnn-VSI "${CaffeMobilenetV2-Armnn-VSI_sources}")

    set(CaffeResNet-Armnn-VSI_sources
        CaffeResNet-Armnn.cpp
        ../CaffePreprocessor.hpp
        ../CaffePreprocessor.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    CaffeParserTest(CaffeResNet-Armnn-VSI "${CaffeResNet-Armnn-VSI_sources}")

    set(CaffeSqueezeNet1_0-Armnn-VSI_sources
        CaffeSqueezeNet1_0-Armnn.cpp
        ../CaffePreprocessor.hpp
        ../CaffePreprocessor.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    CaffeParserTest(CaffeSqueezeNet1_0-Armnn-VSI "${CaffeSqueezeNet1_0-Armnn-VSI_sources}")

    set(CaffeSqueezeNet1_1-Armnn-VSI_sources
        CaffeSqueezeNet1_1-Armnn.cpp
        ../CaffePreprocessor.hpp
        ../CaffePreprocessor.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    CaffeParserTest(CaffeSqueezeNet1_1-Armnn-VSI "${CaffeSqueezeNet1_1-Armnn-VSI_sources}")

    set(CaffeVGG-Armnn-VSI_sources
        CaffeVGG-Armnn.cpp
        ../CaffePreprocessor.hpp
        ../CaffePreprocessor.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    CaffeParserTest(CaffeVGG-Armnn-VSI "${CaffeVGG-Armnn-VSI_sources}")

    set(CaffeYolo-Armnn-VSI_sources
        CaffeYolo-Armnn.cpp
        ../YoloDatabase.hpp
        ../YoloDatabase.cpp
        ../YoloInferenceTest.hpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    CaffeParserTest(CaffeYolo-Armnn-VSI "${CaffeYolo-Armnn-VSI_sources}")
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

    #set(TfMnist-Armnn_sources
    #    TfMnist-Armnn/TfMnist-Armnn.cpp
    #    MnistDatabase.hpp
    #    MnistDatabase.cpp)
    #TfParserTest(TfMnist-Armnn "${TfMnist-Armnn_sources}")

    #set(TfCifar10-Armnn_sources
    #    TfCifar10-Armnn/TfCifar10-Armnn.cpp
    #    Cifar10Database.hpp
    #    Cifar10Database.cpp)
    #TfParserTest(TfCifar10-Armnn "${TfCifar10-Armnn_sources}")

    set(TfMobileNet-Armnn-VSI_sources
        TfMobileNet-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfParserTest(TfMobileNet-Armnn-VSI "${TfMobileNet-Armnn-VSI_sources}")

    set(TfInceptionV3-Armnn-VSI_sources
        TfInceptionV3-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfParserTest(TfInceptionV3-Armnn-VSI "${TfInceptionV3-Armnn-VSI_sources}")

    #set(TfResNext-Armnn_sources
    #    TfResNext_Quantized-Armnn/TfResNext_Quantized-Armnn.cpp
    #    CaffePreprocessor.hpp
    #    CaffePreprocessor.cpp)
    #TfParserTest(TfResNext-Armnn "${TfResNext-Armnn_sources}")
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

	set(TfLiteMnasNet-Armnn-VSI_sources
        TfLiteMnasNet-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(TfLiteMnasNet-Armnn-VSI "${TfLiteMnasNet-Armnn-VSI_sources}")

    set(TfLiteMobileNetSsd-Armnn-VSI_sources
        TfLiteMobileNetSsd-Armnn.cpp
        ../MobileNetSsdDatabase.hpp
        ../MobileNetSsdInferenceTest.hpp
        ../ObjectDetectionCommon.hpp)
    TfLiteParserTest(TfLiteMobileNetSsd-Armnn-VSI "${TfLiteMobileNetSsd-Armnn-VSI_sources}")

    set(TfLiteDensenetFloat-Armnn-VSI_sources
        TfLiteDensenetFloat-Armnn.cpp
        ../MobileNetSsdDatabase.hpp
        ../MobileNetSsdInferenceTest.hpp
        ../ObjectDetectionCommon.hpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(TfLiteDensenetFloat-Armnn-VSI "${TfLiteDensenetFloat-Armnn-VSI_sources}")

    #set(TfLiteMobilenetQuantized-Armnn_sources
    #    TfLiteMobilenetQuantized-Armnn.cpp
    #    ../ImagePreprocessor.hpp
    #    ../ImagePreprocessor.cpp)
    #TfLiteParserTest(TfLiteMobilenetQuantized-Armnn "${TfLiteMobilenetQuantized-Armnn_sources}")

    #set(TfLiteResNetV2-Armnn_sources
    #    TfLiteResNetV2-Armnn.cpp
    #    ../ImagePreprocessor.hpp
    #    ../ImagePreprocessor.cpp)
    #TfLiteParserTest(TfLiteResNetV2-Armnn "${TfLiteResNetV2-Armnn_sources}")

    set(TfLiteSqueezenetFloat-Armnn-VSI_sources
        TfLiteSqueezenetFloat-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(TfLiteSqueezenetFloat-Armnn-VSI "${TfLiteSqueezenetFloat-Armnn-VSI_sources}")

    set(TfLiteInceptionV2Quantized-Armnn-VSI_sources
        TfLiteInceptionV2Quantized-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(TfLiteInceptionV2Quantized-Armnn-VSI "${TfLiteInceptionV2Quantized-Armnn-VSI_sources}")

    set(TfLiteInceptionV3Quantized-Armnn-VSI_sources
        TfLiteInceptionV3Quantized-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(TfLiteInceptionV3Quantized-Armnn-VSI "${TfLiteInceptionV3Quantized-Armnn-VSI_sources}")

    set(TfLiteInceptionV3Float-Armnn-VSI_sources
        TfLiteInceptionV3Float-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(TfLiteInceptionV3Float-Armnn-VSI "${TfLiteInceptionV3Float-Armnn-VSI_sources}")

    set(TfLiteInceptionV4Quantized-Armnn-VSI_sources
        TfLiteInceptionV4Quantized-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(TfLiteInceptionV4Quantized-Armnn-VSI "${TfLiteInceptionV4Quantized-Armnn-VSI_sources}")

    set(TfLiteInceptionV4Float-Armnn-VSI_sources
        TfLiteInceptionV4Float-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(TfLiteInceptionV4Float-Armnn-VSI "${TfLiteInceptionV4Float-Armnn-VSI_sources}")

    set(TfLiteResnetV2Float-Armnn-VSI_sources
        TfLiteResnetV2Float-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(TfLiteResnetV2Float-Armnn-VSI "${TfLiteResnetV2Float-Armnn-VSI_sources}")

    set(TfLiteMobilenetV1Float-Armnn-VSI_sources
        TfLiteMobilenetV1Float-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(TfLiteMobilenetV1Float-Armnn-VSI "${TfLiteMobilenetV1Float-Armnn-VSI_sources}")

    set(TfLiteInceptionV1Quantized-Armnn-VSI_sources
        TfLiteInceptionV1Quantized-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(TfLiteInceptionV1Quantized-Armnn-VSI "${TfLiteInceptionV1Quantized-Armnn-VSI_sources}")

    set(TfLiteMobilenetV1Quantized-Armnn-VSI_sources
        TfLiteMobilenetV1Quantized-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(TfLiteMobilenetV1Quantized-Armnn-VSI "${TfLiteMobilenetV1Quantized-Armnn-VSI_sources}")

    set(TfLiteMobilenetV2Quantized-Armnn-VSI_sources
        TfLiteMobilenetV2Quantized-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(TfLiteMobilenetV2Quantized-Armnn-VSI "${TfLiteMobilenetV2Quantized-Armnn-VSI_sources}")

    set(TfLiteInceptionResnetV2Float-Armnn-VSI_sources
        TfLiteInceptionResnetV2Float-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(TfLiteInceptionResnetV2Float-Armnn-VSI "${TfLiteInceptionResnetV2Float-Armnn-VSI_sources}")
endif()
