/****************************************************************************
*
*    Copyright (c) 2020 Vivante Corporation
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

#pragma once

#include <backendsCommon/TensorHandle.hpp>
#include <backendsCommon/Workload.hpp>
#include <backendsCommon/WorkloadData.hpp>
#include "TNpuWorkloads.hpp"

namespace armnn {
template <typename armnn::DataType... DataTypes>
class NpuDepthToSpaceWorkload : public TNpuWorkload<DepthToSpaceQueueDescriptor, DataTypes...> {
   public:
    using base_type = TNpuWorkload<DepthToSpaceQueueDescriptor, DataTypes...>;
    explicit NpuDepthToSpaceWorkload(const DepthToSpaceQueueDescriptor& descriptor,
                                     const WorkloadInfo& info)
        : TNpuWorkload<DepthToSpaceQueueDescriptor, DataTypes...>(descriptor, info),
          m_BlockSize(descriptor.m_Parameters.m_BlockSize),
          m_DataLayout(descriptor.m_Parameters.m_DataLayout) {
        std::vector<uint32_t> inOperandIds;
        // Add input operand
        auto inputPtr = dynamic_cast<NpuTensorHandler*>(descriptor.m_Inputs[0]);
        if (inputPtr) {
            inOperandIds.push_back(this->AddOperandAndSetValue(
                inputPtr->GetTensorInfo(), inputPtr->GetShape(), nullptr));
        }
        // Add block size operand
        inOperandIds.push_back(this->AddOperandAndSetValue(m_BlockSize));
        // Add layout operand
        int32_t layoutCode = m_DataLayout == armnn::DataLayout::NCHW
                                 ? int32_t(nnrt::DataLayout::NCHW)
                                 : int32_t(nnrt::DataLayout::NHWC);
        inOperandIds.push_back(this->AddOperandAndSetValue(layoutCode));

        // Add output operand
        std::vector<uint32_t> outOperandIds;
        auto outputPtr = dynamic_cast<NpuTensorHandler*>(descriptor.m_Outputs[0]);
        if (outputPtr) {
            outOperandIds.push_back(this->AddOperandAndSetValue(
                outputPtr->GetTensorInfo(), outputPtr->GetShape(), nullptr));
        }

        this->AddOperation(nnrt::OperationType::DEPTH_TO_SPACE,
                           inOperandIds.size(),
                           inOperandIds.data(),
                           outOperandIds.size(),
                           outOperandIds.data());
    }

   private:
    uint32_t m_BlockSize;
    armnn::DataLayout m_DataLayout;
};
using NpuDepthToSpaceFloat32Workload = NpuDepthToSpaceWorkload<armnn::DataType::Float32>;
using NpuDepthToSpaceFloat16Workload = NpuDepthToSpaceWorkload<armnn::DataType::Float16>;
using NpuDepthToSpaceUint8Workload = NpuDepthToSpaceWorkload<armnn::DataType::QAsymmU8>;
}  // namespace armnn
