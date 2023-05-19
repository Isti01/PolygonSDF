#pragma once

#include "../../Source/Editor/Command/StackCommand.h"

namespace psdf
{

class TestCommand : public StackCommand
{
  public:
    using SharedPtr = std::shared_ptr<TestCommand>;

    static SharedPtr create();

    Shape::SharedPtr perform(const Shape::SharedPtr &polygon) const override;
    std::string getName() const override;

  private:
    TestCommand() = default;
};

} // namespace psdf
