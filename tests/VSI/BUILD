package(
    default_visibility = ["//visibility:public"],
    features = ["-parse_headers"],
)

load("@bazel_tools//tools/build_defs/pkg:pkg.bzl", "pkg_tar")

cc_binary(
    name = "TfMobileNet-Armnn",
    linkstatic = False,
    copts = ['-std=c++1z'],
    srcs = ["TfMobileNet-Armnn.cpp"],
    deps = ["@armnn//:inference-Tf"],
    data = ["@tf_model//:mobilenet_v1_1.0_224.tf"],
)

pkg_tar(
    name = "TfMobileNet-Armnn_pkg",
    srcs = [
        ":TfMobileNet-Armnn",
        "@tf_model//:mobilenet_v1_1.0_224.tf",
    ],
    deps = [
        "//:base_pkg",
    ],
    package_dir = "TfMobileNet-Armnn_pkg",
)

cc_binary(
    name = "TfInceptionV3-Armnn",
    linkstatic = False,
    copts = ['-std=c++1z'],
    srcs = ["TfInceptionV3-Armnn.cpp"],
    deps = ["@armnn//:inference-Tf"],
    data = ["@tf_model//:inception_v3.tf"],
)

cc_binary(
    name = "TfLiteMobilenetV1Float-Armnn",
    linkstatic = False,
    copts = ['-std=c++1z', '-DARMNN_TF_LITE_PARSER'],
    srcs = ["TfLiteMobilenetV1Float-Armnn.cpp"],
    deps = ["@armnn//:inference-Tflite"] +
            ["@boost//:boost_atomic"],
    data = ["@tflite_model//:mobilenet_v1_1.0_224-Armnn.tflite"],
)

cc_binary(
    name = "TfLiteMnasNet-Armnn",
    linkstatic = False,
    copts = ['-std=c++1z', '-DARMNN_TF_LITE_PARSER'],
    srcs = ["TfLiteMnasNet-Armnn.cpp"],
    deps = ["@armnn//:inference-Tflite"] +
            ["@boost//:boost_atomic"],
    data = ["@tflite_model//:mnasnet_1.3_224.tflite"],
)

cc_binary(
    name = "TfLiteMobileNetSsd-Armnn",
    linkstatic = False,
    copts = ['-std=c++1z', '-DARMNN_TF_LITE_PARSER'],
    srcs = ["TfLiteMobileNetSsd-Armnn.cpp"],
    deps = ["@armnn//:inference-Tflite"] +
            ["@boost//:boost_atomic"],
    data = ["@tflite_model//:ssd_mobilenet_v1.tflite"],
)

cc_binary(
    name = "TfLiteMobilenetV1Quantized-Armnn",
    linkstatic = False,
    copts = ['-std=c++1z', '-DARMNN_TF_LITE_PARSER'],
    srcs = ["TfLiteMobilenetV1Quantized-Armnn.cpp"],
    deps = ["@armnn//:inference-Tflite"] +
            ["@boost//:boost_atomic"],
    data = ["@tflite_model//:mobilenet_v1_1.0_224_quant-Armnn.tflite"],
)

cc_binary(
    name = "TfLiteMobilenetV2Quantized-Armnn",
    linkstatic = False,
    copts = ['-std=c++1z', '-DARMNN_TF_LITE_PARSER'],
    srcs = ["TfLiteMobilenetV2Quantized-Armnn.cpp"],
    deps = ["@armnn//:inference-Tflite"] +
            ["@boost//:boost_atomic"],
    data = ["@tflite_model//:mobilenet_v2_1.0_224_quant-Armnn.tflite"],
)

cc_binary(
    name = "TfLiteInceptionV1Quantized-Armnn",
    linkstatic = False,
    copts = ['-std=c++1z', '-DARMNN_TF_LITE_PARSER'],
    srcs = ["TfLiteInceptionV1Quantized-Armnn.cpp"],
    deps = ["@armnn//:inference-Tflite"] +
            ["@boost//:boost_atomic"],
    data = ["@tflite_model//:inception_v1_quant-Armnn.tflite"],
)

cc_binary(
   name = "TfLiteInceptionV2Quantized-Armnn",
   linkstatic = False,
   copts = ['-std=c++1z', '-DARMNN_TF_LITE_PARSER'],
   srcs = ["TfLiteInceptionV2Quantized-Armnn.cpp"],
   deps = ["@armnn//:inference-Tflite"] +
           ["@boost//:boost_atomic"],
   data = ["@tflite_model//:inception_v2_quant-Armnn.tflite"],
)

cc_binary(
    name = "TfLiteInceptionV3Quantized-Armnn",
    linkstatic = False,
    copts = ['-std=c++1z', '-DARMNN_TF_LITE_PARSER'],
    srcs = ["TfLiteInceptionV3Quantized-Armnn.cpp"],
    deps = ["@armnn//:inference-Tflite"] +
            ["@boost//:boost_atomic"],
    data = ["@tflite_model//:inception_v3_quant-Armnn.tflite"],
)

cc_binary(
    name = "TfLiteInceptionV4Quantized-Armnn",
    linkstatic = False,
    copts = ['-std=c++1z', '-DARMNN_TF_LITE_PARSER'],
    srcs = ["TfLiteInceptionV4Quantized-Armnn.cpp"],
    deps = ["@armnn//:inference-Tflite"] +
            ["@boost//:boost_atomic"],
    data = ["@tflite_model//:inception_v4_quant-Armnn.tflite"],
)

cc_binary(
    name = "TfLiteResnetV2Float-Armnn",
    linkstatic = False,
    copts = ['-std=c++1z', '-DARMNN_TF_LITE_PARSER'],
    srcs = ["TfLiteResnetV2Float-Armnn.cpp"],
    deps = ["@armnn//:inference-Tflite"] +
            ["@boost//:boost_atomic"],
    data = ["@tflite_model//:resnet_v2_50-Armnn.tflite"],
)

cc_binary(
    name = "TfLiteSqueezenetFloat-Armnn",
    linkstatic = False,
    copts = ['-std=c++1z', '-DARMNN_TF_LITE_PARSER'],
    srcs = ["TfLiteSqueezenetFloat-Armnn.cpp"],
    deps = ["@armnn//:inference-Tflite"] +
            ["@boost//:boost_atomic"],
    data = ["@tflite_model//:squeezenet-Armnn.tflite"],
)

cc_binary(
    name = "TfLiteDensenetFloat-Armnn",
    linkstatic = False,
    copts = ['-std=c++1z', '-DARMNN_TF_LITE_PARSER'],
    srcs = ["TfLiteDensenetFloat-Armnn.cpp"],
    deps = ["@armnn//:inference-Tflite"] +
            ["@boost//:boost_atomic"],
    data = ["@tflite_model//:densenet-Armnn.tflite"],
)

cc_binary(
    name = "TfLiteInceptionV3Float-Armnn",
    linkstatic = False,
    copts = ['-std=c++1z', '-DARMNN_TF_LITE_PARSER'],
    srcs = ["TfLiteInceptionV3Float-Armnn.cpp"],
    deps = ["@armnn//:inference-Tflite"] +
            ["@boost//:boost_atomic"],
    data = ["@tflite_model//:inception_v3-Armnn.tflite"],
)

cc_binary(
    name = "TfLiteInceptionV4Float-Armnn",
    linkstatic = False,
    copts = ['-std=c++1z', '-DARMNN_TF_LITE_PARSER'],
    srcs = ["TfLiteInceptionV4Float-Armnn.cpp"],
    deps = ["@armnn//:inference-Tflite"] +
            ["@boost//:boost_atomic"],
    data = ["@tflite_model//:inception_v4-Armnn.tflite"],
)

cc_binary(
    name = "TfLiteInceptionResnetV2Float-Armnn",
    linkstatic = False,
    copts = ['-std=c++1z', '-DARMNN_TF_LITE_PARSER'],
    srcs = ["TfLiteInceptionResnetV2Float-Armnn.cpp"],
    deps = ["@armnn//:inference-Tflite"] +
            ["@boost//:boost_atomic"],
    data = ["@tflite_model//:inception_resnet_v2-Armnn.tflite"],
)

cc_binary(
    name = "CaffeAlexNet-Armnn",
    linkstatic = False,
    copts = ['-std=c++1z'],
    srcs = [
            "CaffeAlexNet-Armnn.cpp",
            ],
    deps = ["@armnn//:inference-Caffe"],
    data = ["@caffe_model//:alexnet.caffe"],
)

cc_binary(
    name = "CaffeResNet-Armnn",
    linkstatic = False,
    copts = ['-std=c++1z'],
    srcs = [
            "CaffeResNet-Armnn.cpp",
            ],
    deps = ["@armnn//:inference-Caffe"],
    data = ["@caffe_model//:resnet_v1_50.caffe"],
)

cc_binary(
    name = "CaffeInception_BN-Armnn",
    linkstatic = False,
    copts = ['-std=c++1z'],
    srcs = [
            "CaffeInception_BN-Armnn.cpp",
            ],
    deps = ["@armnn//:inference-Caffe"],
    data = ["@caffe_model//:inception_v1.caffe"],
)

cc_binary(
    name = "CaffeMobilenetV1-Armnn",
    linkstatic = False,
    copts = ['-std=c++1z'],
    srcs = [
            "CaffeMobilenetV1-Armnn.cpp",
            ],
    deps = ["@armnn//:inference-Caffe"],
    data = ["@caffe_model//:mobilenet_v1.caffe"],
)

cc_binary(
    name = "CaffeMobilenetV2-Armnn",
    linkstatic = False,
    copts = ['-std=c++1z'],
    srcs = [
            "CaffeMobilenetV2-Armnn.cpp",
            ],
    deps = ["@armnn//:inference-Caffe"],
    data = ["@caffe_model//:mobilenet_v2.caffe"],
)

cc_binary(
    name = "CaffeInceptionV3-Armnn",
    linkstatic = False,
    copts = ['-std=c++1z'],
    srcs = [
            "CaffeInceptionV3-Armnn.cpp",
            ],
    deps = ["@armnn//:inference-Caffe"],
    data = ["@caffe_model//:inception_v3.caffe"],
)

cc_binary(
    name = "CaffeInceptionV4-Armnn",
    linkstatic = False,
    copts = ['-std=c++1z'],
    srcs = [
            "CaffeInceptionV4-Armnn.cpp",
            ],
    deps = ["@armnn//:inference-Caffe"],
    data = ["@caffe_model//:inception_v4.caffe"],
)

cc_binary(
    name = "CaffeSqueezeNet1_0-Armnn",
    linkstatic = False,
    copts = ['-std=c++1z'],
    srcs = [
            "CaffeSqueezeNet1_0-Armnn.cpp",
            ],
    deps = ["@armnn//:inference-Caffe"],
    data = ["@caffe_model//:squeezenet_v1.0.caffe"],
)

cc_binary(
    name = "CaffeSqueezeNet1_1-Armnn",
    linkstatic = False,
    copts = ['-std=c++1z'],
    srcs = [
            "CaffeSqueezeNet1_1-Armnn.cpp",
            ],
    deps = ["@armnn//:inference-Caffe"],
    data = ["@caffe_model//:squeezenet_v1.1.caffe"],
)

cc_binary(
    name = "CaffeVGG-Armnn",
    linkstatic = False,
    copts = ['-std=c++1z'],
    srcs = [
            "CaffeVGG-Armnn.cpp",
            ],
    deps = ["@armnn//:inference-Caffe"],
    data = ["@caffe_model//:vgg16.caffe"],
)

cc_binary(
    name = "CaffeYolo-Armnn",
    linkstatic = False,
    copts = ['-std=c++1z'],
    srcs = [
            "CaffeYolo-Armnn.cpp",
            ],
    deps = ["@armnn//:inference-Caffe"],
    data = ["@caffe_model//:yolo_v1.caffe"],
)

