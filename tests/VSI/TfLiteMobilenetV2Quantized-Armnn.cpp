//
// Copyright © 2017 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//
#include "tests/ImagePreprocessor.hpp"
#include "tests/InferenceTest.hpp"
#include "armnnTfLiteParser/ITfLiteParser.hpp"

#include "boost/program_options.hpp"
#include <fstream>

using namespace armnnTfLiteParser;

std::vector<ImageSet> ParseDataset(const std::string& filename)
{
    std::ifstream read(filename);
    std::vector<ImageSet> imageSet;
    if (read.is_open())
    {
        // Get the images and the correct corresponding label from the given file
        for (std::string line; std::getline(read, line);)
        {
            stringstream ss(line);
            std::string image_name;
            std::string label;
            getline(ss, image_name, ' ');
            getline(ss, label, ' ');
            imageSet.push_back(ImageSet(image_name, std::stoi(label)));
        }
    }
    else
    {
        imageSet.push_back(ImageSet("space_shuttle_224x224.jpg", 813));
    };
    return imageSet;
}

std::string GetLabelsFilenameFromOptions(int argc, char* argv[])
{
    namespace po = boost::program_options;
    po::options_description desc("Validation Options");
    std::string fn("");
    desc.add_options()
        ("labels", po::value<std::string>(&fn), "Filename of a text file where in each line contains an image "
            "filename and the correct label the network should predict when fed that image");
    po::variables_map vm;
    po::parsed_options parsed = po::command_line_parser(argc, argv).options(desc).allow_unregistered().run();
    po::store(parsed, vm);
    if (vm.count("labels"))
    {
        fn = vm["labels"].as<std::string>();
    }
    return fn;
}


int main(int argc, char* argv[])
{
    int retVal = EXIT_FAILURE;
    try
    {
        // Coverity fix: The following code may throw an exception of type std::length_error.
        const std::string labels_file = GetLabelsFilenameFromOptions(argc,argv);
        std::vector<ImageSet> imageSet = ParseDataset(labels_file);
        std::vector<unsigned int> indices(imageSet.size());
        std::generate(indices.begin(), indices.end(), [n = 0] () mutable { return n++; });

        armnn::TensorShape inputTensorShape({ 1, 224, 224, 3  });

        using DataType = uint8_t;
        using DatabaseType = ImagePreprocessor<DataType>;
        using ParserType = armnnTfLiteParser::ITfLiteParser;
        using ModelType = InferenceModel<ParserType, DataType>;

        // Coverity fix: ClassifierInferenceTestMain() may throw uncaught exceptions.
        retVal = armnn::test::ClassifierInferenceTestMain<DatabaseType,
                                                          ParserType>(
                     argc, argv,
                     "mobilenet_v2_1.0_224_quant.tflite", // model name
                     true,                                // model is binary
                     "input",                             // input tensor name
                     "output", // output tensor name
                     indices,                             // vector of indices to select which images to validate
                     [&imageSet](const char* dataDir, const ModelType & model) {
                         // we need to get the input quantization parameters from
                         // the parsed model
                         return DatabaseType(
                             dataDir,
                             224,
                             224,
                             imageSet,
                             1);
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
