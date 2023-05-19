#pragma once

#include "StackCommand.h"

namespace psdf
{

class CalculateSdfPlaneAlgorithmCommand : public StackCommand
{
  public:
    using SharedPtr = std::shared_ptr<CalculateSdfPlaneAlgorithmCommand>;
    static SharedPtr create(SdfPlaneAlgorithmExecutionDesc executionDesc);

    Shape::SharedPtr perform(const Shape::SharedPtr &pShape) const override;
    std::string getName() const override;
    SdfPlaneAlgorithmExecutionDesc getExecutionDesc() const;

  protected:
    CalculateSdfPlaneAlgorithmCommand(SdfPlaneAlgorithmExecutionDesc executionDesc);

  private:
    SdfPlaneAlgorithmExecutionDesc mExecutionDesc;
};

} // namespace psdf
