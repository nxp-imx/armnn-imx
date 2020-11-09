# VSI NPU backend changelog

### 07/30/2020
* Enabled TransposeConvolution2d unit test
* Fixed l2_norm and local_response_norm
* Added Abs/Exp/Sqrt/Neg in elementwise unary
* Added LogSoftmax support
* Added Argmax and Argmin support
* Removed AvgPool unit tests with zp=-1
* Added DetectionPostProcess support
* Added InstanceNorm support
* Added DepthToSpace support
* Added GREATER_EQUAL, NOT_EQUAL, LESS, LESS_EQUAL ops

### 07/17/2020
* Added Slice support

### 05/26/2020
* Update to 20.02 interface.

### 04/22/2020
* Updated 2D convolution OverflowPolicy from WRAP to SATURATE
* Support dilation in depthwise convolution

### 04/08/2020
* Update depth_to_space to be compatible with ovxlib
* Enabled RSQRT layer
* Added Linear Activation support - float32 only

### 03/20/2020
* Enabled VSI NPU to be built as a dynamic backend
* Added Gather support
* Disabled Splitter unit test
* Removed deprecated function IsSplitterSupported
* Execution performance improvement (switching from startCompute to compute function)

### 03/06/2020
* Added Splitter support
* Added Equal support
* Added Greater support
* Fixed build errors with TensorHandler and FusedType

# Known Limitations

### 20.02
* OpenCL backend is not supported. i.MX8 devices do not support Arm NN / ACL OpenCL requirements.
* Unexpected predictions on some floating point models and ConstantLinearActivation were fixed. No known issues.

### 19.08.01
* ConstantLinearActivation producing incorrect results on the VSI NPU backend
* Unexpected predictions observed on MobileNet v1 floating point models from the [TFLite hosted model site](https://www.tensorflow.org/lite/guide/hosted_models) running on the VSI NPU backend

### 19.08

* Activation - Linear/Square, Greater, Equal, DilatedDepthWiseConvolution,FakeQuantization (only in TF parser), Gather, Normalization - AlgorithmChannel::Within, Splitter, Debug (use CpuRef version instead) layers not supported on the VsiNpu backend
*  Softmax and Reshape float layers on the VsiNpu backend produce incorrect results
