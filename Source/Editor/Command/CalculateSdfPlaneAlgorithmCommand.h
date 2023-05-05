#pragma once

#include "StackCommand.h"

namespace psdf
{

class CalculateSdfPlaneAlgorithmCommand : public StackCommand
{
  public:
    using SharedPtr = std::shared_ptr<CalculateSdfPlaneAlgorithmCommand>;
    static SharedPtr create(SdfPlaneAlgorithmExecutionDesc executionDesc);

    Polygon::SharedPtr perform(const Polygon::SharedPtr &polygon) const override;
    std::string getName() const override;
    SdfPlaneAlgorithmExecutionDesc getExecutionDesc() const;

  protected:
    CalculateSdfPlaneAlgorithmCommand(SdfPlaneAlgorithmExecutionDesc executionDesc);

  private:
    SdfPlaneAlgorithmExecutionDesc mExecutionDesc;
};

} // namespace psdf
