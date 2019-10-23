# UnitTests
include(CheckIncludeFiles)

# Setup the inference test framework
#set(inference_test_sources
    #../ClassifierTestCaseData.hpp
    #../InferenceModel.hpp
    #../InferenceTest.hpp
    #../InferenceTest.inl
    #../InferenceTest.cpp
    #../InferenceTestImage.hpp
    #../InferenceTestImage.cpp)

#add_library_ex(inferenceTest STATIC ${inference_test_sources})
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

    set(VSI-CaffeInceptionV4-Armnn_sources
        CaffeInceptionV4-Armnn.cpp
        ../CaffePreprocessor.hpp
        ../CaffePreprocessor.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    CaffeParserTest(VSI-CaffeInceptionV4-Armnn "${VSI-CaffeInceptionV4-Armnn_sources}")

    set(VSI-CaffeMobilenetV1-Armnn_sources
        CaffeMobilenetV1-Armnn.cpp
        ../CaffePreprocessor.hpp
        ../CaffePreprocessor.cpp
        ../ImagePreprocessor.hpp
        ../ImagePreprocessor.cpp)
    CaffeParserTest(VSI-CaffeMobilenetV1-Armnn "${VSI-CaffeMobilenetV1-Armnn_sources}")

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
