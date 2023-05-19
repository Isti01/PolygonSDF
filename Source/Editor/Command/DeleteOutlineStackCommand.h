#pragma once

#include "StackCommand.h"

namespace psdf
{

class DeleteOutlineStackCommand : public StackCommand
{
  public:
    using SharedPtr = std::shared_ptr<DeleteOutlineStackCommand>;

    static SharedPtr create(size_t outlineIndex);

    Shape::SharedPtr perform(const Shape::SharedPtr &pShape) const override;
    std::string getName() const override;

  protected:
    DeleteOutlineStackCommand(size_t outlineIndex);

  private:
    size_t mOutlineIndex;
};

} // namespace psdf
