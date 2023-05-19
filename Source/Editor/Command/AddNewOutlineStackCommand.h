#pragma once

#include "StackCommand.h"

namespace psdf
{
using namespace psdf;

class AddNewOutlineStackCommand : public StackCommand
{
  public:
    using SharedPtr = std::shared_ptr<AddNewOutlineStackCommand>;
    static SharedPtr create(Outline newOutline);

    Shape::SharedPtr perform(const Shape::SharedPtr &shape) const override;
    std::string getName() const override;

  protected:
    AddNewOutlineStackCommand(Outline newOutline);

  private:
    Outline mNewOutline;
};

} // namespace psdf
