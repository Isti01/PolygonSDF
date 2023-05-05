#pragma once

#include "../../Source/Editor/Command/StackCommand.h"

namespace psdf
{

class TestCommand : public StackCommand
{
  public:
    using SharedPtr = std::shared_ptr<TestCommand>;

    static SharedPtr create();

    Polygon::SharedPtr perform(const Polygon::SharedPtr &polygon) const override;
    std::string getName() const override;

  private:
    TestCommand() = default;
};

} // namespace psdf
