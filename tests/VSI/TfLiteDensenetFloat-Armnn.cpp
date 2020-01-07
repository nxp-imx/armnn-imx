//
// Copyright © 2017 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//
#include "tests/InferenceTest.hpp"
#include "tests/ImagePreprocessor.hpp"
#include "armnnTfLiteParser/ITfLiteParser.hpp"

using namespace armnnTfLiteParser;

int main(int argc, char* argv[])
{
    int retVal = EXIT_FAILURE;
    try
    {
        std::vector<ImageSet> imageSet =
        {
            {"space_shuttle_224x224.jpg", 813},
        };

        armnn::TensorShape inputTensorShape({ 1, 224, 224, 3  });

        using DataType = float;
        using DatabaseType = ImagePreprocessor<DataType>;
        using ParserType = armnnTfLiteParser::ITfLiteParser;
        using ModelType = InferenceModel<ParserType, DataType>;

        // Coverity fix: ClassifierInferenceTestMain() may throw uncaught exceptions.
        retVal = armnn::test::ClassifierInferenceTestMain<DatabaseType,
                                                          ParserType>(
                     argc, argv,
                     "densenet.tflite",         // model name
                     true,                                // model is binary
                     "Placeholder",                             // input tensor name
                     "softmax_tensor", // output tensor name
                     { 0, 1, 2 },                         // test images to test with as above
                     [&imageSet](const char* dataDir, const ModelType & model) {
                         // we need to get the input quantization parameters from
                         // the parsed model
                         return DatabaseType(
                             dataDir,
                             224,
                             224,
                             imageSet,
                             1,
                             {{123.68f, 116.78f, 103.94f}},
                             {{255.0f, 255.0f, 255.0f}},
                             DatabaseType::DataFormat::NHWC,
                             1
                             );
                     },
                     &inputTensorShape);
    }
    catch (const std::exception& e)
    {
        // Coverity fix: BOOST_LOG_TRIVIAL (typically used to report errors) may throw an
        // exception of type std::length_error.
        // Using stderr instead in this context as there is no point in nesting try-catch blocks here.
        std::cerr << "WARNING: " << *argv << ": An error has occurred when running "
                     "the classifier inference tests: " << e.what() << std::endl;
    }
    return retVal;
}
