//
// Copyright 2021 NXP
// SPDX-License-Identifier: MIT
//

#include <armnn/delegate/armnn_delegate.hpp>
#include <tensorflow/lite/kernels/register.h>

#include <chrono>
#include <stdlib.h>
#include <time.h>

using namespace std::chrono;
using namespace tflite;

int main()
{
    // load model and allocate tensors
    std::unique_ptr<tflite::FlatBufferModel> model = tflite::FlatBufferModel::BuildFromFile("mobilenet_v1_1.0_224_quant.tflite");        
    auto interpreter = std::make_unique<Interpreter>();
    tflite::ops::builtin::BuiltinOpResolver resolver;    
    tflite::InterpreterBuilder(*model, resolver)(&interpreter);
    
    if (interpreter->AllocateTensors() != kTfLiteOk)
    {
        std::cout << "Failed to allocate tensors!" << std::endl;
        return EXIT_FAILURE;
    }    

    // fill input tensors with random numbers from 0 to 255
    srand (time(NULL));
    uint8_t* input = interpreter->typed_input_tensor<uint8_t>(0);    
    for (int i = 0; i < (3 * 224 * 224); ++i) {
        input[i] = rand() % 256;
    }  
    
    // set delegate options
    std::vector<armnn::BackendId> backends = { armnn::Compute::VsiNpu, armnn::Compute::CpuAcc, armnn::Compute::CpuRef };
    armnnDelegate::DelegateOptions delegateOptions(backends);
    std::unique_ptr<TfLiteDelegate, decltype(&armnnDelegate::TfLiteArmnnDelegateDelete)>
                        theArmnnDelegate(armnnDelegate::TfLiteArmnnDelegateCreate(delegateOptions),
                                         armnnDelegate::TfLiteArmnnDelegateDelete);

    // modify graph
    if (interpreter->ModifyGraphWithDelegate(theArmnnDelegate.get()) != kTfLiteOk)
    {
        std::cout << "Failed to modify graph!" << std::endl;
        return EXIT_FAILURE;
    }

    // first inference including warm-up time
    auto start = high_resolution_clock::now();
    if (interpreter->Invoke() != kTfLiteOk)
    {
        std::cout << "Failed to run first inference!" << std::endl;
        return EXIT_FAILURE;
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    std::cout << "Warm-up time: " << static_cast<float>(duration.count()) / 1000.f << " ms" << std::endl;

    // second inference
    start = high_resolution_clock::now();
    if (interpreter->Invoke() != kTfLiteOk)
    {
        std::cout << "Failed to run second inference!" << std::endl;
        return EXIT_FAILURE;
    }
    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start);
    std::cout << "Inference time: " << static_cast<float>(duration.count()) / 1000.f << " ms" << std::endl;
    
    // retrieve results
    uint8_t* output = interpreter->typed_output_tensor<uint8_t>(0);    
    std::vector<uint8_t> values(output, &output[1000]);
    auto result = std::max_element(std::begin(values), std::end(values));
    std::cout << "TOP 1: " << std::distance(values.begin(), result) << std::endl;

    return EXIT_SUCCESS;
}
