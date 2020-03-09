# Arm NN

Arm NN is a key component of the [machine learning platform](https://mlplatform.org/), which is part of the [Linaro Machine Intelligence Initiative](https://www.linaro.org/news/linaro-announces-launch-of-machine-intelligence-initiative/). For more information on the machine learning platform and Arm NN, see: <https://mlplatform.org/>, also there is further Arm NN information available from <https://developer.arm.com/products/processors/machine-learning/arm-nn>

There is a getting started guide here using TensorFlow: <https://developer.arm.com/technologies/machine-learning-on-arm/developer-material/how-to-guides/configuring-the-arm-nn-sdk-build-environment-for-tensorflow>

There is a getting started guide here using TensorFlow Lite: <https://developer.arm.com/technologies/machine-learning-on-arm/developer-material/how-to-guides/configuring-the-arm-nn-sdk-build-environment-for-tensorflow-lite>

There is a getting started guide here using Caffe: <https://developer.arm.com/technologies/machine-learning-on-arm/developer-material/how-to-guides/configuring-the-arm-nn-sdk-build-environment-for-caffe>

There is a getting started guide here using ONNX: <https://developer.arm.com/technologies/machine-learning-on-arm/developer-material/how-to-guides/configuring-the-arm-nn-sdk-build-environment-for-onnx>

There is a guide for backend development: [Backend development guide](src/backends/README.md)

NXP additionally provides the VSI NPU backend and updates for the i.MX8 platform. The VSI NPU backend is one of the components of [eIQ™ ML Software Development Environment](https://www.nxp.com/design/software/development-software/eiq-ml-development-environment:EIQ) and greatly accelerates inference using i.MX8 GPUs and NPUs.

### Build Instructions

Arm and NXP test the build system of Arm NN with the following build environments:

* Android NDK: [How to use Android NDK to build Arm NN](BuildGuideAndroidNDK.md)
* Cross compilation from x86_64 Ubuntu to arm64 Linux: [Arm NN Cross Compilation](BuildGuideCrossCompilation.md)
* Cross compilation from x86_64 Ubuntu to arm64 using Yocto SDK (for NXP i.MX8 boards): [Arm NN Yocto SDK Cross Compilation](BuildGuideCrossCompilationYocto.md)
* Native compilation under aarch64 Debian 9

Arm NN is written using portable C++14 and the build system uses [CMake](https://cmake.org/), therefore it is possible to build for a wide variety of target platforms, from a wide variety of host environments.

The armnn/tests directory contains tests used during Arm NN development. Many of them depend on third-party IP, model protobufs and image files not distributed with Arm NN. The dependencies of some of the tests are available freely on the Internet, for those who wish to experiment.

The 'armnn/samples' directory contains SimpleSample.cpp, a very basic example of the ArmNN SDK API in use.

The 'ExecuteNetwork' program, in armnn/tests/ExecuteNetwork, has no additional dependencies beyond those required by Arm NN and the model parsers. It takes any model and any input tensor, and simply prints out the output tensor. Run it with no arguments to see command-line help.

The 'ArmnnConverter' program, in armnn/src/armnnConverter, has no additional dependencies beyond those required by Arm NN and the model parsers. It takes a model in TensorFlow format and produces a serialized model in Arm NN format. Run it with no arguments to see command-line help. Note that this program can only convert models for which all operations are supported by the serialization tool [src/armnnSerializer](src/armnnSerializer/README.md).

The 'ArmnnQuantizer' program, in armnn/src/armnnQuantizer, has no additional dependencies beyond those required by Arm NN and the model parsers. It takes a 32-bit float network and converts it into a quantized asymmetric 8-bit or quantized symmetric 16-bit network.
Static quantization is supported by default but dynamic quantization can be enabled if CSV file of raw input tensors is specified. Run it with no arguments to see command-line help.

Note that Arm NN needs to be built against a particular version of [ARM's Compute Library](https://github.com/ARM-software/ComputeLibrary). The get_compute_library.sh in the scripts subdirectory will clone the compute library from the review.mlplatform.org github repository into a directory alongside armnn named 'clframework' and checks out the correct revision. Additionally if the VSI NPU backend is enabled a specific version of VeriSilicon's NNRT (Neural Network Runtime) is required. CMake checks this during configuration.

### License

Arm NN is provided under the [MIT](https://spdx.org/licenses/MIT.html) license.
See [LICENSE](LICENSE) for more information. Contributions to this project are accepted under the same license.

Individual files contain the following tag instead of the full license text.

    SPDX-License-Identifier: MIT

This enables machine processing of license information based on the SPDX License Identifiers that are available here: http://spdx.org/licenses/

### Contributions

The Arm NN project welcomes contributions. For more details on contributing to Arm NN see the [Contributing page](https://mlplatform.org/contributing/) on the [MLPlatform.org](https://mlplatform.org/) website, or see the [Contributor Guide](ContributorGuide.md).

### Release Information

See the [GitHub Release page](https://github.com/ARM-software/armnn/releases) for a list of new features and [Known Limitations](KnownLimitations.md) for a list a known limitations related to each release.
