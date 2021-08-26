### Integrate the Arm NN Delegate into your C++ project

The following example demonstrates a sample project using a TF Lite Interpreter delegating workloads to the Arm NN framework.

1) Activate the Yocto SDK environment on your host machine for cross-compiling (make sure that TensorFlow Lite and Arm NN are installed):
source <yocto_sdk_install_dir>/environment-setup-aarch64-poky-linux

2) Download code from: https://source.codeaurora.org/external/imx/armnn-imx/tree/delegate/samples?h=lf-5.10.52-2.1.0 and cross-compile using:
$CXX -o armnn_delegate_example armnn_delegate_example.cpp -larmnn -larmnnDelegate -ltensorflow-lite

3) Copy armnn_delegate_example to your board and execute, the output should look similar to the following:

```
root@imx8mpevk:~# ./armnn_delegate_example
INFO: TfLiteArmnnDelegate: Created TfLite ArmNN delegate.
Warm-up time: 4662.1 ms
Inference time: 2.809 ms
TOP 1: 412
```

Now let's have a look at the code available for the previous example.

1) First we need to load a model, create the TF Lite Interpreter, and allocate input tensors of the appropriate size. You may use a different tflite model from the one supplied below for your own project:

```cpp
std::unique_ptr<tflite::FlatBufferModel> model = tflite::FlatBufferModel::BuildFromFile("/usr/bin/tensorflow-lite-2.5.0/examples/mobilenet_v1_1.0_224_quant.tflite");        
auto interpreter = std::make_unique<Interpreter>();
tflite::ops::builtin::BuiltinOpResolver resolver;    
tflite::InterpreterBuilder(*model, resolver)(&interpreter);

if (interpreter->AllocateTensors() != kTfLiteOk)
{
    std::cout << "Failed to allocate tensors!" << std::endl;
    return 0;
} 
```

2) Then we need to fill the tensor with some data. You may load the data from a file, or simply fill the buffer with random numbers. Note that in our example we are using a quantized model, so the input should be in <0, 255> range and that the input tensor has 3 channels and 224x224 input:

```cpp
srand (time(NULL));
uint8_t* input = interpreter->typed_input_tensor<uint8_t>(0);    
for (int i = 0; i < (3 * 224 * 224); ++i) {
    input[i] = rand() % 256;
}  
```

3) To configure the Arm NN backend, we have to specify the delegate options. Backends are assigned to individual layers from left to right based on layer support:
```cpp
std::vector<armnn::BackendId> backends = { armnn::Compute::VsiNpu, armnn::Compute::CpuAcc, armnn::Compute::CpuRef };
armnnDelegate::DelegateOptions delegateOptions(backends);
std::unique_ptr<TfLiteDelegate, decltype(&armnnDelegate::TfLiteArmnnDelegateDelete)>
                    theArmnnDelegate(armnnDelegate::TfLiteArmnnDelegateCreate(delegateOptions),
                                     armnnDelegate::TfLiteArmnnDelegateDelete);
```

4) Now we must apply the delegate to the graph. This partitions the graph into subgraphs which will be executed using the Arm NN delegate if possible. The rest will fall back to the CPU:
```cpp
if (interpreter->ModifyGraphWithDelegate(theArmnnDelegate.get()) != kTfLiteOk)
{
    std::cout << "Failed to modify graph!" << std::endl;
    return EXIT_FAILURE;
}
```

5) Afterwards we may run inference, retrieve the result, and process it. The output from the mobilenet model is a softmax array, so for example to retrieve the top labels, we would have to apply an argmax function. Note that in the example, we are running inference 2 times. That is due to the usage of the VsiNpu backend which has a significant warm-up time.
```cpp
if (interpreter->Invoke() != kTfLiteOk)
{
    std::cout << "Failed to run second inference!" << std::endl;
    return EXIT_FAILURE;
}
...
uint8_t* output = interpreter->typed_output_tensor<uint8_t>(0);
```