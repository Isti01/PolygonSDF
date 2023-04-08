#pragma once

#include "StackCommand.h"

namespace psdf
{

class CalculateSdfPlaneAlgorithmCommand : public StackCommand
{
  public:
    using SharedPtr = std::shared_ptr<CalculateSdfPlaneAlgorithmCommand>;
    static SharedPtr create();

    Polygon::SharedPtr perform(const Polygon::SharedPtr &polygon) const override;
    std::string getName() const override;

  protected:
    CalculateSdfPlaneAlgorithmCommand() = default;
};

} // namespace psdf
