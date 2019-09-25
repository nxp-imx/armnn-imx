/****************************************************************************
*
*    Copyright (c) 2019 Vivante Corporation
*
*    Permission is hereby granted, free of charge, to any person obtaining a
*    copy of this software and associated documentation files (the "Software"),
*    to deal in the Software without restriction, including without limitation
*    the rights to use, copy, modify, merge, publish, distribute, sublicense,
*    and/or sell copies of the Software, and to permit persons to whom the
*    Software is furnished to do so, subject to the following conditions:
*
*    The above copyright notice and this permission notice shall be included in
*    all copies or substantial portions of the Software.
*
*    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
*    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
*    DEALINGS IN THE SOFTWARE.
*
*****************************************************************************/

#include "NpuInputWorkload.hpp"
#include "NpuBackend.hpp"
#include "Profiling.hpp"
#include "NpuTensorHandler.hpp"

#include <armnn/BackendId.hpp>
#include <boost/log/trivial.hpp>

namespace armnn {
NpuInputWorkload::NpuInputWorkload(const InputQueueDescriptor& descriptor, const WorkloadInfo& info)
    : CopyMemGenericWorkload(descriptor, info) {

        m_InputTensorSz = info.m_InputTensorInfos[0].GetNumBytes();
    }

void NpuInputWorkload::Execute() const {
    ARMNN_SCOPED_PROFILING_EVENT(Compute::VsiNpu, "NpuInputWorkload_Execute");

    assert(m_Data.m_Inputs.size() == 1);
    assert(m_Data.m_Outputs.size() == 1);
    ITensorHandle* inputTensor = m_Data.m_Inputs[0];
    NpuTensorHandler* outputTensor = dynamic_cast<NpuTensorHandler*>(m_Data.m_Outputs[0]);

    if (inputTensor && outputTensor) {
        outputTensor->SetMemoryAddr(inputTensor->Map(), m_InputTensorSz);
    } else {
        BOOST_LOG_TRIVIAL(fatal) << "Tensor type doesn't NpuTensorHandle";
    }
}

}  // namespace armnn
