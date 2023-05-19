#pragma once

#include "StackCommand.h"
namespace psdf
{

class SetShapeStackCommand : public StackCommand
{
  public:
    static StackCommand::SharedPtr create(Shape::SharedPtr pShape);

    [[nodiscard]] Shape::SharedPtr perform(const Shape::SharedPtr &pShape) const override;

    [[nodiscard]] std::string getName() const override;

    [[nodiscard]] Shape::SharedPtr getShape() const;

  protected:
    SetShapeStackCommand(Shape::SharedPtr pShape);

  private:
    Shape::SharedPtr mpShape;
};

} // namespace psdf
