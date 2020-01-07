//
// Copyright © 2017 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//
#include "tests/InferenceTest.hpp"
#include "tests/ImagePreprocessor.hpp"
#include "armnnCaffeParser/ICaffeParser.hpp"

int main(int argc, char* argv[])
{
    int retVal = EXIT_FAILURE;
    try
    {
        // Coverity fix: The following code may throw an exception of type std::length_error.
        std::vector<ImageSet> imageSet =
        {
            {"space_shuttle_299x299.jpg", 233}
        };

        using DataType = float;
        using DatabaseType = ImagePreprocessor<float>;
        using ParserType = armnnCaffeParser::ICaffeParser;
        using ModelType = InferenceModel<ParserType, DataType>;

        // Coverity fix: ClassifierInferenceTestMain() may throw uncaught exceptions.
        retVal = armnn::test::ClassifierInferenceTestMain<DatabaseType, ParserType>(
                    argc, argv, "inception_v3.caffemodel", true,
                    "input", "prob", { 0 },
                    [&imageSet](const char* dataDir, const ModelType&) {
                        return DatabaseType(dataDir, 299, 299, imageSet, 1, {{128, 128, 128}}, {{128, 128, 128}}, DatabaseType::DataFormat::NCHW, 1);
                    });
    }
    catch (const std::exception& e)
    {
        // Coverity fix: BOOST_LOG_TRIVIAL (typically used to report errors) may throw an
        // exception of type std::length_error.
        // Using stderr instead in this context as there is no point in nesting try-catch blocks here.
        std::cerr << "WARNING: CaffeInception_BN-Armnn: An error has occurred when running "
                     "the classifier inference tests: " << e.what() << std::endl;
    }
    return retVal;
}
