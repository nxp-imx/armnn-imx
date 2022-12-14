//
// Copyright © 2017 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//

#pragma once

#include <armnn/Descriptors.hpp>

#include <backendsCommon/Workload.hpp>
#include <arm_compute/runtime/CL/functions/CLSpaceToDepthLayer.h>

namespace armnn
{
arm_compute::Status ClSpaceToDepthWorkloadValidate(const TensorInfo& input,
                                                   const TensorInfo& output,
                                                   const SpaceToDepthDescriptor& descriptor);

class ClSpaceToDepthWorkload : public BaseWorkload<SpaceToDepthQueueDescriptor>
{
public:
    ClSpaceToDepthWorkload(const SpaceToDepthQueueDescriptor& descriptor,
                           const WorkloadInfo& info,
                           const arm_compute::CLCompileContext& clCompileContext);
    void Execute() const override;

private:
    mutable arm_compute::CLSpaceToDepthLayer m_Layer;
};

} //namespace armnn
