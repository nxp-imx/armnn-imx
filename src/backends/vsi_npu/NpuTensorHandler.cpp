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

#include "NpuTensorHandler.hpp"

#include <string>
#include <armnn/TypesUtils.hpp>

#include <boost/log/trivial.hpp>

namespace armnn
{
// VSI NPU TensorHandler
void NpuTensorHandler::SetOperandId(unsigned int id)
{
    m_OperandId = id;
}

void NpuTensorHandler::Allocate()
{
}

TensorShape NpuTensorHandler::GetStrides() const
{
    TensorShape shape(m_TensorInfo.GetShape());
    auto size = GetDataTypeSize(m_TensorInfo.GetDataType());
    auto runningSize = size;
    std::vector<unsigned int> strides(shape.GetNumDimensions());
    auto lastIdx = shape.GetNumDimensions()-1;
    for (unsigned int i=0; i < lastIdx ; i++)
    {
        strides[lastIdx-i] = runningSize;
        runningSize *= shape[lastIdx-i];
    }
    strides[0] = runningSize;
    return TensorShape(shape.GetNumDimensions(), strides.data());
}

void NpuTensorHandler::CopyOutTo(void* memory) const
{
    getMemoryReady();

    std::memcpy(memory, m_Memory.get(), m_TensorInfo.GetNumBytes());
}

void NpuTensorHandler::CopyInFrom(const void* memory)
{
    getMemoryReady();

    std::memcpy(m_Memory.get(), memory, m_TensorInfo.GetNumBytes());
}

TensorShape NpuTensorHandler::GetShape() const
{
    return m_TensorInfo.GetShape();
}

void* NpuTensorHandler::Map(bool blocking)
{
    getMemoryReady();
    return static_cast<void*>(m_Memory.get());
}

const void* NpuTensorHandler::Map(bool blocking) const
{
    getMemoryReady();
    if (m_ReadOnlyMem) {
        return m_ReadOnlyMem;
    } else {
        return static_cast<const void*>(m_Memory.get());
    }
}

void* NpuTensorHandler::GetMemArea()
{
    return m_Memory.get();
}

void NpuTensorHandler::Unmap() const
{}

void NpuTensorHandler::Unmap()
{}

void NpuTensorHandler::getMemoryReady() const {
    bool IsInputTensor = m_ModelStack.empty();
    // TODO: InputHandle can be already allocated memory
    // If InputHandle already allocated memory: means it allocated by previous sub-graph allocated on our backend.
    // In this case, we should not be here because we didn't ask memory allocation internally.
    if (IsInputTensor) {
        if (m_ReadOnlyMem) {
            return;
        }
        m_Memory.reset(new uint8_t[m_TensorInfo.GetNumBytes()]);
        // Keep this track random caculation error issue
        BOOST_LOG_TRIVIAL(info) << "allocated memory at" << m_Memory.get() << ", size = "<<m_TensorInfo.GetNumBytes();
        return;
    }

    // Rest code for output handler
    if (m_Memory) {
        // "Warn-Start NN execution"
        if (!m_ModelShell) {
            assert(false);
            BOOST_LOG_TRIVIAL(debug) << "Model prepare failed: check previous log for error log";
            return;
        }
        BOOST_LOG_TRIVIAL(info) << "Warn-Start NN execution" ;
        m_ModelShell->Execute();
        return;
    }

    m_Memory.reset(new uint8_t[m_TensorInfo.GetNumBytes()]);

    auto mergedModel = adaption::utils::MergeModels(m_ModelStack);

    // IAmLastHope means: I must construct ModelShell object and execute the model for other output
    // usually, the last accessed output is the "last hope"
    bool IAmLastHope = true;
    for (auto& outputHandle : mergedModel->second.second) {
        if (outputHandle != this && !outputHandle->m_Memory) {
            outputHandle->Map(true); // recursive call for all output
            IAmLastHope = false;
        }
    }

    if (IAmLastHope){ // Only execute model while access last output tensor
        m_ModelShell.reset(new ModelShell(std::move(mergedModel)));
        // finalModel ready to run
        m_ModelShell->Execute();
    } else { // find model shell object created by "Last Hope"
        for (auto& OutputHandle: mergedModel->second.second) {
            auto sharedModelShell = OutputHandle->shareModelShell();
            if (sharedModelShell) {
                m_ModelShell = sharedModelShell;
            }
        }
    }
}

MemorySourceFlags NpuTensorHandler::GetImportFlags() const {
    // only support malloc
    return static_cast<MemorySourceFlags>(MemorySource::Malloc);
}

bool NpuTensorHandler::Import(void* memory, MemorySource source) {
    if ((static_cast<MemorySourceFlags>(source) &
        static_cast<MemorySourceFlags>(MemorySource::Malloc)) != 0) {
        SetMemoryAddr(memory, GetTensorInfo().GetNumBytes());
        return true;
    } else {
        return false;
    }
}
}
