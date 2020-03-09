# Known Limitations

### 19.08

* Activation - Linear/Square, Greater, Equal, DilatedDepthWiseConvolution,FakeQuantization (only in TF parser), Gather, Normalization - AlgorithmChannel::Within, Splitter, Debug (use CpuRef version instead) layers not supported on the VsiNpu backend
*  Softmax and Reshape float layers on the VsiNpu backend produce incorrect results
