//
// Copyright © 2019 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//

#pragma once

#include <armnn/Descriptors.hpp>

#include <backendsCommon/Workload.hpp>

#include <arm_compute/runtime/CL/functions/CLDepthToSpaceLayer.h>

namespace armnn
{

arm_compute::Status ClDepthToSpaceWorkloadValidate(const TensorInfo& input,
                                                   const TensorInfo& output,
                                                   const DepthToSpaceDescriptor& descriptor);

class ClDepthToSpaceWorkload : public BaseWorkload<DepthToSpaceQueueDescriptor>
{
public:
    ClDepthToSpaceWorkload(const DepthToSpaceQueueDescriptor& descriptor,
                           const WorkloadInfo& info,
                           const arm_compute::CLCompileContext& clCompileContext);
    void Execute() const override;

private:
    mutable arm_compute::CLDepthToSpaceLayer m_Layer;
};

} // namespace armnn
