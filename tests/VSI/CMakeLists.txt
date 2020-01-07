# UnitTests
include(CheckIncludeFiles)

# Setup the inference test framework
set(inference_test_sources
    ../ClassifierTestCaseData.hpp
    ../InferenceModel.hpp
    ../InferenceTest.hpp
    ../InferenceTest.inl
    ../InferenceTest.cpp
    ../InferenceTestImage.hpp
    ../InferenceTestImage.cpp)

add_library_ex(inferenceTest STATIC ${inference_test_sources})
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
        if(VSINPU_LIBRARIES)
            target_link_libraries(${testName} ${VSINPU_LIBRARIES})
        endif()
        target_link_libraries(${testName}
            ${Boost_SYSTEM_LIBRARY}
            ${Boost_FILESYSTEM_LIBRARY}
            ${Boost_PROGRAM_OPTIONS_LIBRARY})
        addDllCopyCommands(${testName})
    endmacro()

    set(CaffeAlexNet-Armnn_sources
        CaffeAlexNet-Armnn.cpp
        ../CaffePreprocessor.hpp
        ../CaffePreprocessor.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    CaffeParserTest(CaffeAlexNet-Armnn "${CaffeAlexNet-Armnn_sources}")

    set(CaffeInception_BN-Armnn_sources
        CaffeInception_BN-Armnn.cpp
        ../CaffePreprocessor.hpp
        ../CaffePreprocessor.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    CaffeParserTest(CaffeInception_BN-Armnn "${CaffeInception_BN-Armnn_sources}")

    set(CaffeInceptionV3-Armnn_sources
        CaffeInceptionV3-Armnn.cpp
        ../CaffePreprocessor.hpp
        ../CaffePreprocessor.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    CaffeParserTest(CaffeInceptionV3-Armnn "${CaffeInceptionV3-Armnn_sources}")

    set(CaffeInceptionV4-Armnn_sources
        CaffeInceptionV4-Armnn.cpp
        ../CaffePreprocessor.hpp
        ../CaffePreprocessor.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    CaffeParserTest(CaffeInceptionV4-Armnn "${CaffeInceptionV4-Armnn_sources}")

    set(CaffeMobilenetV1-Armnn_sources
        CaffeMobilenetV1-Armnn.cpp
        ../CaffePreprocessor.hpp
        ../CaffePreprocessor.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    CaffeParserTest(CaffeMobilenetV1-Armnn "${CaffeMobilenetV1-Armnn_sources}")

    set(CaffeMobilenetV2-Armnn_sources
        CaffeMobilenetV2-Armnn.cpp
        ../CaffePreprocessor.hpp
        ../CaffePreprocessor.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    CaffeParserTest(CaffeMobilenetV2-Armnn "${CaffeMobilenetV2-Armnn_sources}")

    set(CaffeResNet-Armnn_sources
        CaffeResNet-Armnn.cpp
        ../CaffePreprocessor.hpp
        ../CaffePreprocessor.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    CaffeParserTest(CaffeResNet-Armnn "${CaffeResNet-Armnn_sources}")

    set(CaffeSqueezeNet1_0-Armnn_sources
        CaffeSqueezeNet1_0-Armnn.cpp
        ../CaffePreprocessor.hpp
        ../CaffePreprocessor.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    CaffeParserTest(CaffeSqueezeNet1_0-Armnn "${CaffeSqueezeNet1_0-Armnn_sources}")

    set(CaffeSqueezeNet1_1-Armnn_sources
        CaffeSqueezeNet1_1-Armnn.cpp
        ../CaffePreprocessor.hpp
        ../CaffePreprocessor.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    CaffeParserTest(CaffeSqueezeNet1_1-Armnn "${CaffeSqueezeNet1_1-Armnn_sources}")

    set(CaffeVGG-Armnn_sources
        CaffeVGG-Armnn.cpp
        ../CaffePreprocessor.hpp
        ../CaffePreprocessor.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    CaffeParserTest(CaffeVGG-Armnn "${CaffeVGG-Armnn_sources}")

    set(CaffeYolo-Armnn_sources
        CaffeYolo-Armnn.cpp
        ../YoloDatabase.hpp
        ../YoloDatabase.cpp
        ../YoloInferenceTest.hpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    CaffeParserTest(CaffeYolo-Armnn "${CaffeYolo-Armnn_sources}")
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
        if(VSINPU_LIBRARIES)
            target_link_libraries(${testName} ${VSINPU_LIBRARIES})
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

    set(TfMobileNet-Armnn_sources
        TfMobileNet-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfParserTest(TfMobileNet-Armnn "${TfMobileNet-Armnn_sources}")

    set(TfInceptionV3-Armnn_sources
        TfInceptionV3-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfParserTest(TfInceptionV3-Armnn "${TfInceptionV3-Armnn_sources}")

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
        if(VSINPU_LIBRARIES)
            target_link_libraries(${testName} ${VSINPU_LIBRARIES})
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

	set(TfLiteMnasNet-Armnn_sources
        TfLiteMnasNet-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(TfLiteMnasNet-Armnn "${TfLiteMnasNet-Armnn_sources}")

    set(TfLiteMobileNetSsd-Armnn_sources
        TfLiteMobileNetSsd-Armnn.cpp
        ../MobileNetSsdDatabase.hpp
        ../MobileNetSsdInferenceTest.hpp
        ../ObjectDetectionCommon.hpp)
    TfLiteParserTest(TfLiteMobileNetSsd-Armnn "${TfLiteMobileNetSsd-Armnn_sources}")

    set(TfLiteDensenetFloat-Armnn_sources
        TfLiteDensenetFloat-Armnn.cpp
        ../MobileNetSsdDatabase.hpp
        ../MobileNetSsdInferenceTest.hpp
        ../ObjectDetectionCommon.hpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(TfLiteDensenetFloat-Armnn "${TfLiteDensenetFloat-Armnn_sources}")

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

    set(TfLiteSqueezenetFloat-Armnn_sources
        TfLiteSqueezenetFloat-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(TfLiteSqueezenetFloat-Armnn "${TfLiteSqueezenetFloat-Armnn_sources}")

    set(TfLiteInceptionV2Quantized-Armnn_sources
        TfLiteInceptionV2Quantized-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(TfLiteInceptionV2Quantized-Armnn "${TfLiteInceptionV2Quantized-Armnn_sources}")

    set(TfLiteInceptionV3Quantized-Armnn_sources
        TfLiteInceptionV3Quantized-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(TfLiteInceptionV3Quantized-Armnn "${TfLiteInceptionV3Quantized-Armnn_sources}")

    set(TfLiteInceptionV3Float-Armnn_sources
        TfLiteInceptionV3Float-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(TfLiteInceptionV3Float-Armnn "${TfLiteInceptionV3Float-Armnn_sources}")

    set(TfLiteInceptionV4Quantized-Armnn_sources
        TfLiteInceptionV4Quantized-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(TfLiteInceptionV4Quantized-Armnn "${TfLiteInceptionV4Quantized-Armnn_sources}")

    set(TfLiteInceptionV4Float-Armnn_sources
        TfLiteInceptionV4Float-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(TfLiteInceptionV4Float-Armnn "${TfLiteInceptionV4Float-Armnn_sources}")

    set(TfLiteResnetV2Float-Armnn_sources
        TfLiteResnetV2Float-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(TfLiteResnetV2Float-Armnn "${TfLiteResnetV2Float-Armnn_sources}")

    set(TfLiteMobilenetV1Float-Armnn_sources
        TfLiteMobilenetV1Float-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(TfLiteMobilenetV1Float-Armnn "${TfLiteMobilenetV1Float-Armnn_sources}")

    set(TfLiteInceptionV1Quantized-Armnn_sources
        TfLiteInceptionV1Quantized-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(TfLiteInceptionV1Quantized-Armnn "${TfLiteInceptionV1Quantized-Armnn_sources}")

    set(TfLiteMobilenetV1Quantized-Armnn_sources
        TfLiteMobilenetV1Quantized-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(TfLiteMobilenetV1Quantized-Armnn "${TfLiteMobilenetV1Quantized-Armnn_sources}")

    set(TfLiteMobilenetV2Quantized-Armnn_sources
        TfLiteMobilenetV2Quantized-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(TfLiteMobilenetV2Quantized-Armnn "${TfLiteMobilenetV2Quantized-Armnn_sources}")

    set(TfLiteInceptionResnetV2Float-Armnn_sources
        TfLiteInceptionResnetV2Float-Armnn.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    TfLiteParserTest(TfLiteInceptionResnetV2Float-Armnn "${TfLiteInceptionResnetV2Float-Armnn_sources}")
endif()
