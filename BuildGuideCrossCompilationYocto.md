# How to Cross-Compile ArmNN on x86_64 for arm64 using Yocto SDK

*  [Introduction](#introduction)
*  [Cross-compiling ToolChain](#installCCT)
*  [Build and install Google's Protobuf library](#buildProtobuf)
*  [Build Boost library for arm64](#installBaarch)
*  [Build Compute Library](#buildCL)
*  [Build ArmNN](#buildANN)
*  [Run Unit Tests](#unittests)
*  [Build Caffe for x86_64](#buildCaffe)
*  [Caffe Parser](#caffeparser)
*  [Tensorflow Parser](#tfparser)
*  [Tensorflow Lite Parser](#tfliteparser)
*  [ONNX Parser](#onnxparser)
*  [VSI NPU backend](#vsinpubackend)
*  [Troubleshooting and Errors](#troubleshooting)


#### <a name="introduction">Introduction</a>
These are the step by step instructions on Cross-Compiling ArmNN under an x86_64 system to target an Arm64 system using Yocto SDK. This build flow has been tested with Ubuntu 16.04.
The instructions assume basic Linux knowledge and show how to build the ArmNN core library and it's dependencies.

#### <a name="installCCT">Cross-compiling ToolChain</a>
* Install Yocto SDK, the script will guide you through all the steps, e.g.:
    ```
    ./fsl-imx-internal-xwayland-glibc-x86_64-imx-image-core-aarch64-toolchain-5.4-zeus.sh
    ```
* Libraries such as protobuf require both arm64 and x86_64 versions. In order to build an x86_64 version, you must make sure that a standard compiler is run. In case you previously ran the script to set environmental variables, reset your shell (close/open). To set environmental variables:
    ```
    source <yocto_sdk_path>/environment-setup-aarch64-poky-linux
    ```
* *Note: There are typically 2 folders in `<yocto_sdk_path>/sysroots` - aarch64-poky-linux and x86_64-pokysdk-linux. x86_64-pokysdk-linux directory contains the x86_64 environment, e.g. the cross-compiler from x86_64 to arm64 is located in `<yocto_sdk_path>/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux`. On the other hand `<yocto_sdk_path>/sysroots/aarch64-poky-linux` contains the arm64 environment, from which you typically cannot execute binaries on your Linux machine, but you may use includes, libraries, etc. for cross-compilation.*
#### <a name="buildProtobuf">Build and install Google's Protobuf library</a>

* Download [protobuf-all-3.5.1.tar.gz](https://github.com/protocolbuffers/protobuf/releases/tag/v3.5.1).
* Extract:
    ```bash
    tar -zxvf protobuf-all-3.5.1.tar.gz
    cd protobuf-3.5.1
    ```
* Build a native (x86_64) version of the protobuf libraries and compiler (protoc). Also make sure you did not run the environment-setup script previously, otherwise reset your environment:
  (Requires cUrl, autoconf, llibtool, and other build dependencies if not previously installed: sudo apt install curl autoconf libtool build-essential g++)
    ```bash
    mkdir x86_64_build
    cd x86_64_build
    ../configure --prefix=<protobuf_x86_install_dir>
    make install -j$(nproc)
    ```
* Build the arm64 version of the protobuf libraries:
    ```bash
    source <yocto_sdk_path>/environment-setup-aarch64-poky-linux
    mkdir arm64_build
    cd arm64_build    
    ../configure --host=aarch64-linux \
    --prefix=<protobuf_arm64_install_dir> \
    --with-protoc=<protobuf_x86_install_dir>/bin/protoc
    make install -j$(nproc)
    ```

#### <a name="installBaarch">Build Boost library for arm64</a>
* Download [Boost version 1.64](https://www.boost.org/users/history/version_1_64_0.html). Other versions typically do work, but do not be surprised when they do not.
    ```bash
    tar -zxvf boost_1_64_0.tar.gz
    cd boost_1_64_0
    ```
* Set the cross-compiler to the compiler used in Yocto SDK (it should be located in `<yocto_sdk_path>/sysroots/x86_64-pokysdk-linux/usr/bin/<cross compiler dir>` and should be called e.g. aarch64-poky-linux-g++
    ```bash
    source <yocto_sdk_path>/environment-setup-aarch64-poky-linux
    echo "using gcc : arm : aarch64-poky-linux-g++  --sysroot=<yocto_sdk_path>/sysroots/aarch64-poky-linux ;" > user_config.jam
    ./bootstrap.sh --prefix=<protobuf_arm64_install_dir>
    ./b2 install toolset=gcc-arm link=static cxxflags=-fPIC --with-filesystem --with-test --with-log --with-program_options -j$(nproc) --user-config=user_config.jam
    ```
* *Note: To build as a shared library, remove link=static.*

#### <a name="buildCL">Build Compute Library</a>
* It is recommended to build [NXP's fork of ACL](https://source.codeaurora.org/external/imx/arm-computelibrary-imx), which is tested to run on the i.MX8 platform. [Official ACL](https://github.com/ARM-software/ComputeLibrary) can also be used, but might lead to unexpected compile failures. Make sure that the ArmNN (in the next step) and ACL versions match. Additionally scons is used for building. It is a python package and should be supported for both Python 2.7 and 3.x versions. It can be installed using `pip install scons`:
    ```bash
    git clone https://source.codeaurora.org/external/imx/arm-computelibrary-imx -b imx_20.02
    cd arm-computelibrary-imx
    source <yocto_sdk_path>/environment-setup-aarch64-poky-linux
    scons Werror=0 -j$(nproc) neon=1 opencl=1 os=linux arch=arm64-v8a build=cross_compile embed_kernels=1 gles_compute=0
    ```

#### <a name="buildANN">Build ArmNN</a>
* Compile ArmNN for arm64:
    ```bash
    git clone https://source.codeaurora.org/external/imx/armnn-imx -b branches/armnn_19_08
    cd armnn-imx
    mkdir build
    cd build
    ```

* Use CMake to configure your build. Make sure to set paths based on your environment. Below is an example:
    ```bash
    source <yocto_sdk_path>/environment-setup-aarch64-poky-linux
    cmake .. \
    -DARMCOMPUTE_ROOT=<arm-computelibrary-imx_dir> \
    -DARMCOMPUTE_BUILD_DIR=<arm-computelibrary-imx_dir>/build \
    -DARMCOMPUTENEON=1 -DARMCOMPUTECL=1 -DARMNNREF=1 -DVSI_NPU=0 \
    -DBOOST_ROOT=<boost_arm64_install_dir> \
    -DPROTOBUF_ROOT=<protobuf_arm64_install_dir> \
    -DPROTOBUF_LIBRARY_DEBUG=<protobuf_arm64_install_dir>/lib/libprotobuf.so.15.0.1 \
    -DPROTOBUF_LIBRARY_RELEASE=<protobuf_arm64_install_dir>/lib/libprotobuf.so.15.0.1
    ```
* Run the build
    ```bash
    make -j$(nproc)
    ```
* Well done! Now you should have a minimal ArmNN environment ready including only the shared library and UnitTests (enabled by default using build option *BUILD_UNIT_TESTS*) for ACL backends.

#### <a name="unittests">Run Unit Tests</a>
* Copy the build folder to an arm64 linux machine. You may exclude all those CMakes to create an archive with the following command:
    ```bash
    tar --exclude='*.o' --exclude='*.os' --exclude='*.cmake' --exclude='CMake*' --exclude='Makefile' --exclude='samples' --exclude='src' -czvf armnn-imx_20.02.tar.gz *
    ```
* Copy the protobuf shared library (and links) to the ArmNN build folder and set *LD_LIBRARY_PATH* to include it:
    ```bash
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:<armnn-imx_dir>/build
    ```
* Run the UnitTests:
    ```bash
    ./UnitTests
    ```

#### <a name="vsinpubackend">VSI NPU backend</a>
* [NXP's fork of ArmNN](https://source.codeaurora.org/external/imx/armnn-imx) contains VeriSilicon's VSI NPU backend, which uses OpenVX to accelerate neural networks on GPU.
    ```
    -DVSI_NPU=1
    ```
* Use *VSI_NPU* build option (disabled by default) to enable it.
* VSI NPU backend has several dependencies - OpenVX, ovxlib and NNRT. [OpenVX](https://www.khronos.org/openvx/) is a standard for computer vision designed by Khronos and it is implemented as a driver targeted for specific GPUs. NNRT is VeriSilicon's library to process neural networks and ovxlib is a layer between the OpenVX driver and NNRT. If the Yocto SDK you are using already includes a GPU driver version targeted for development, CMake should find all the dependencies. If not or if you are using a customized driver, you need to set the following build variables. You may only use the *_ROOT* suffix to find both libraries and includes or you may specify libraries and includes separately using *_INCLUDE* and *_LIB*. It is better to either use *_ROOT* alone or *_INCLUDE* and *_LIB* together. After configuration is done, make sure to check the output if correct directories were found:
* For OpenVX:
    ```bash
    -DOPENVX_DRIVER_ROOT=<openvx_driver_path> \
    -DOPENVX_DRIVER_INCLUDE=<openvx_include_path> \ # path to VX dir
    -DOPENVX_DRIVER_LIB=<openvx_lib_path> \
    ```
* For NNRT:
    ```bash
    -DNNRT_ROOT=<nnrt_root_dir> \
    -DNNRT_INCLUDE=<nnrt_include_dir> \ # path to nnrt dir
    -DNNRT_LIB=<nnrt_lib_dir> \
    ```
* For ovxlib:
    ```bash
    -DOVXLIB_ROOT=<ovxlib_root_dir> \
    -DOVXLIB_INCLUDE=<ovxlib_include_dir> \
    -DOVXLIB_LIB=<ovxlib_lib_dir> \
    ```
* Typically on a Yocto image all libraries are pre-installed, so you do not need to specify any of the paths and CMake finds them in /usr/lib and /usr/include.

#### <a name="buildCaffe">Build Caffe for x86_64</a>
* Ubuntu 16.04 installation. These steps are taken from the [full Caffe installation documentation](http://caffe.berkeleyvision.org/install_apt.html).
* Install dependencies:
    ```bash
    sudo apt-get install libleveldb-dev libsnappy-dev libopencv-dev libhdf5-serial-dev
    sudo apt-get install --no-install-recommends libboost-all-dev
    sudo apt-get install libgflags-dev libgoogle-glog-dev liblmdb-dev
    sudo apt-get install libopenblas-dev
    sudo apt-get install libatlas-base-dev
    ```
* Download [Caffe](https://github.com/BVLC/caffe/releases) (tested on 1.0). 
    ```bash
    tar -zxvf caffe-1.0.tar.gz
    cd caffe-1.0
    cp Makefile.config.example Makefile.config
    ```
* Adjust Makefile.config as necessary for your environment, for example:
    ```
    #CPU only version:
    CPU_ONLY := 1

    #Add hdf5 and protobuf include and library directories (Replace $HOME with explicit /home/username dir):
    INCLUDE_DIRS := $(PYTHON_INCLUDE) /usr/local/include /usr/include/hdf5/serial/ <protobuf_x86_install_dir>/include/
    LIBRARY_DIRS := $(PYTHON_LIB) /usr/local/lib /usr/lib /usr/lib/x86_64-linux-gnu/hdf5/serial/ <protobuf_x86_install_dir>/lib/
    ```
* Setup environment:
    ```bash
    export PATH=<protobuf_x86_install_dir>/bin/:$PATH
    export LD_LIBRARY_PATH=<protobuf_x86_install_dir>/lib/:$LD_LIBRARY_PATH
    ```
* Compilation with Make:
    ```bash
    make all
    make test
    make runtest
    ```
    These should all run without errors, but even when they do not, it is not all that critical.
* Only caffe.pb.h and caffe.pb.cc will be needed when building [ArmNN's Caffe Parser](#caffeparser).

#### <a name="caffeparser">Caffe Parser</a>
Support for using [Caffe](http://caffe.berkeleyvision.org/) models.
* [Build Caffe for x86_64](#buildCaffe)
* Add the following lines to your CMake command to configure your build environment (`src/caffe/proto` should contain *caffe.pb.h* and *caffe.pb.cc*):
    ```
    -DCAFFE_GENERATED_SOURCES=<caffe build path>/src/caffe/proto \
    -DBUILD_CAFFE_PARSER=1 \
    ```

#### <a name="tfparser">Tensorflow Parser</a>
Support for using [Tensorflow](https://www.tensorflow.org/) models.
* Run the script to generate required files. [TensorFlow 1.15.0](https://github.com/tensorflow/tensorflow) is tested, other versions may or may not work:
    ```
    git clone https://github.com/tensorflow/tensorflow.git -b r1.15
    cd tensorflow
    <armnn-imx_dir>/scripts/generate_tensorflow_protobuf.sh <tf_generated_files_dir> <protobuf_x86_install_dir>
    ```

* Add the following lines to your CMake command to configure your build environment:
    ```    
    -DTF_GENERATED_SOURCES=<tf_generated_files_dir>
    -DBUILD_TF_PARSER=1 \
    ```

#### <a name="tfliteparser">Tensorflow Lite Parser</a>
Support for using [Tensorflow Lite](https://www.tensorflow.org/lite) models. Tensorflow Lite is a subset of Tensorflow targeted for embedded. In order to build the parser, the main difference from Tensorflow is that instead of protobuf, it uses [FlatBuffers](https://google.github.io/flatbuffers/index.html#flatbuffers_overview) as a serialization library.


* Clone Tensorflow 1.15.0:
    ```    
    git clone https://github.com/tensorflow/tensorflow.git -b r1.15
    cd tensorflow
    ```
* Make sure to [build FlatBuffers for arm64](#flatbuffers).
* Add the following lines to your CMake command to configure your build environment:
    ```
    -DTF_LITE_GENERATED_PATH=<tensorflow_path>/tensorflow/lite/schema \
    -DTF_LITE_SCHEMA_INCLUDE_PATH=<tensorflow_path>/tensorflow/lite/schema \
    -DFLATBUFFERS_ROOT=<flatbuffers_path> \
    -DFLATBUFFERS_INCLUDE_PATH=<flatbuffers_path>/include \
    -DFLATBUFFERS_LIBRARY=<flatbuffers_path>/libflatbuffers.a \
    -DBUILD_TF_LITE_PARSER=1 \
    ```

#### <a name="flatbuffers">FlatBuffers</a>

FlatBuffers static library is required for the target machine (arm64) in case you are building the TF Lite Parser. Flatc (Flatbuffers compiler) is required for the host machine (x86_64) if you are building the Arm NN Serializer.

* Download [FlatBuffers v1.12.0](https://github.com/google/flatbuffers/releases).
    ```bash 
    tar -zxvf flatbuffers-1.12.0.tar.gz
    cd flatbuffers-1.12.0/
    ```
* Build FlatBuffers without tests and flathash for x86_64:
    ```bash 
    cmake -DCMAKE_BUILD_TYPE=Release -DFLATBUFFERS_BUILD_FLATC=ON -DFLATBUFFERS_BUILD_FLATHASH=OFF -DFLATBUFFERS_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=<flatbuffers_x86_64_install_dir>
    make -j$(nproc)
    make install
    ```
* Make sure to add `-fPIC` to `CMAKE_CXX_FLAGS`. You can achieve this ege by opening *CMakeLists.txt* and adding `set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")` at the end of the file.
* Build FlatBuffers without tests, flathash and flatc for arm64 (you do not need flatc, but it might get useful if you ever compile natively):
    ```bash 
    source <yocto_sdk_path>/environment-setup-aarch64-poky-linux
    cmake -DCMAKE_BUILD_TYPE=Release -DFLATBUFFERS_BUILD_FLATC=OFF -DFLATBUFFERS_BUILD_FLATHASH=OFF -DFLATBUFFERS_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=<flatbuffers_arm64_install_dir>
    make -j$(nproc)
    make install
    ```

#### <a name="onnxparser">ONNX Parser</a>
Support for using [ONNX](https://onnx.ai/) (Open Neural Network Exchange) models. ONNX is an ecosystem and an open format for machine learning and deep learning models originally introduced by Facebook and Microsoft and later accepted as a project in Linux Foundation AI. Use instructions from [ONNX GitHub](https://github.com/onnx/onnx).

* Download [ONNX v.1.6.0](https://github.com/onnx/onnx/releases).
    ```bash
    tar -zxvf onnx-1.6.0.tar.gz
    cd onnx-1.6.0/
    export LD_LIBRARY_PATH=<x86_64_protobuf_install_path>/lib:$LD_LIBRARY_PATH
    mkdir <onnx_generated_files_path>
    <x86_64_protobuf_install_path>/bin/protoc onnx/onnx.proto --proto_path=. --proto_path=<x86_64_protobuf_install_path>/include --cpp_out <onnx_generated_files_path>
    ```
* Add the following lines to your CMake command to configure your build environment:
    ```
    -DBUILD_ONNX_PARSER=1 \
    -DONNX_GENERATED_SOURCES=<onnx_generated_files_path> \
    ```

#### <a name="troubleshooting">Troubleshooting and Errors</a>
#### Warnings originating in ACL's half.hpp:
* You may run into errors caused by warnings from ACL:
    ```
    /home/root/arm-computelibrary-imx/include/half/half.hpp:1681:68: error: conversion from ‘int’ to ‘half_float::detail::uint16’ {aka ‘short unsigned int’} may change value [-Werror=conversion]
    1681 |     return *exp = e+(m>>10), half(binary, (arg.data_&0x8000)|0x3800|(m&0x3FF));
        |                                           ~~~~~~~~~~~~~~~~~~~~~~~~~^~~~~~~~~~
    /home/root/arm-computelibrary-imx/include/half/half.hpp: In static member function ‘static half_float::half half_float::detail::functions::modf(half_float::half, half_float::half*)’:
    /home/root/arm-computelibrary-imx/include/half/half.hpp:1692:58: error: conversion to ‘unsigned int’ from ‘int’ may change the sign of the result [-Werror=sign-conversion]
    1692 |      return *iptr = arg, half(binary, arg.data_&(0x8000U|-(e>0x7C00)));
    ```
* i.MX8 devices do not support OpenCL backend and using it is experimental, so either disable this by setting `-DARMCOMPUTECL=0` or apply the following <a href="https://review.mlplatform.org/c/ml/armnn/+/2690">commit</a> if it's not yet available in your sources.

#### Dynamic linking errors:
* When running binaries (examples, UnitTests, etc.):
    ```
    ./UnitTests: error while loading shared libraries: libboost_unit_test_framework.so.1.71.0: cannot open shared object file: No such file or directory
    ```
    
* Boost is already installed in your Yocto SDK environment and CMake linked it. You may either recompile with your custom boost or copy those boost libs to your arm64 linux machine build folder (assuming it is included in *LD_LIBRARY_PATH*). Boost shared libraries will be found in `<yocto_sdk_path>/sysroots/aarch64-poky-linux/usr/lib`. To force custom boost path add the following lines to your CMake command:
    ```
    -DBOOST_ROOT=$HOME/armnn-devenv/boost_arm64_install \
    -DBoost_LIBRARY_DIR=$HOME/armnn-devenv/boost_arm64_install/lib \
    -DBoost_INCLUDE_DIR=$HOME/armnn-devenv/boost_arm64_install/include \
    ```
* The same may happen even if you linked against a custom boost, but you built it dynamically. Make sure to copy those shared libs to the arm64 linux machine and set LD_LIBRARY_PATH to include the path.

#### Error adding symbols: File in wrong format
* When building armNN:
    ```
    /usr/local/lib/libboost_log.a: error adding symbols: File in wrong format
    collect2: error: ld returned 1 exit status
    CMakeFiles/armnn.dir/build.make:4028: recipe for target 'libarmnn.so' failed
    make[2]: *** [libarmnn.so] Error 1
    CMakeFiles/Makefile2:105: recipe for target 'CMakeFiles/armnn.dir/all' failed
    make[1]: *** [CMakeFiles/armnn.dir/all] Error 2
    Makefile:127: recipe for target 'all' failed
    make: *** [all] Error 2
    ```
* Boost libraries are not compiled for the correct architecture, try recompiling for arm64
##
#### Virtual memory exhausted
* When compiling the boost libraries:
    ```bash
    virtual memory exhausted: Cannot allocate memory
    ```
* Not enough memory available to compile. Increase the amount of RAM or swap space available.

##
#### Unrecognized command line option '-m64'
* When compiling the boost libraries:
    ```bash
    aarch64-linux-gnu-g++: error: unrecognized command line option ‘-m64’
    ```
* Clean the boost library directory before trying to build with a different architecture:
    ```bash
    sudo ./b2 clean
    ```
* It should show the following for arm64:
    ```bash
    - 32-bit                   : no
    - 64-bit                   : yes
    - arm                      : yes
    ```

##
#### Missing libz.so.1
* When compiling armNN:
    ```bash
    /usr/lib/gcc-cross/aarch64-linux-gnu/5/../../../../aarch64-linux-gnu/bin/ld: warning: libz.so.1, needed by /home/<username>/armNN/usr/lib64/libprotobuf.so.15.0.0, not found (try using -rpath or -rpath-link)
    ```

* Missing arm64 libraries for libz.so.1, these can be added by adding a second architecture to dpkg and explicitly installing them:
    ```bash
    sudo dpkg --add-architecture arm64
    sudo apt-get install zlib1g:arm64
    sudo apt-get update
    sudo ldconfig
    ```
* If apt-get update returns 404 errors for arm64 repos refer to section 5 below.
* Alternatively the missing arm64 version of libz.so.1 can be downloaded and installed from a .deb package here:
      https://launchpad.net/ubuntu/wily/arm64/zlib1g/1:1.2.8.dfsg-2ubuntu4
    ```bash
    sudo dpkg -i zlib1g_1.2.8.dfsg-2ubuntu4_arm64.deb
    ```
##
#### Unable to install arm64 packages after adding arm64 architecture
* Using sudo apt-get update should add all of the required repos for arm64 but if it does not or you are getting 404 errors the following instructions can be used to add the repos manually:
* From stackoverflow:
https://askubuntu.com/questions/430705/how-to-use-apt-get-to-download-multi-arch-library/430718
* Open /etc/apt/sources.list with your preferred text editor.

* Mark all the current (default) repos as \[arch=<current_os_arch>], e.g.
    ```bash
    deb [arch=amd64] http://archive.ubuntu.com/ubuntu/ xenial main restricted
    ```
* Then add the following:
    ```bash
    deb [arch=arm64] http://ports.ubuntu.com/ xenial main restricted
    deb [arch=arm64] http://ports.ubuntu.com/ xenial-updates main restricted
    deb [arch=arm64] http://ports.ubuntu.com/ xenial universe
    deb [arch=arm64] http://ports.ubuntu.com/ xenial-updates universe
    deb [arch=arm64] http://ports.ubuntu.com/ xenial multiverse
    deb [arch=arm64] http://ports.ubuntu.com/ xenial-updates multiverse
    deb [arch=arm64] http://ports.ubuntu.com/ xenial-backports main restricted universe multiverse
    ```
* Update and install again:
    ```bash
    sudo apt-get install zlib1g:arm64
    sudo apt-get update
    sudo ldconfig
    ```
##
#### Undefined references to google::protobuf:: functions
* When compiling armNN there are multiple errors of the following type:
    ```
    libarmnnCaffeParser.so: undefined reference to `google::protobuf:*
    ```
* Missing or out of date protobuf compilation libraries.
    Use the command 'protoc --version' to check which version of protobuf is available (version 3.5.1 is required).
    Follow the instructions above to install protobuf 3.5.1
    Note this will require you to recompile Caffe for x86_64
