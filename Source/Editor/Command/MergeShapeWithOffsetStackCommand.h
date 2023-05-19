#pragma once

#include "StackCommand.h"

namespace psdf
{

class MergeShapeWithOffsetStackCommand : public StackCommand
{
  public:
    using SharedPtr = std::shared_ptr<MergeShapeWithOffsetStackCommand>;
    static SharedPtr create(Shape::SharedPtr pShape, Vertex offset);

    Shape::SharedPtr perform(const Shape::SharedPtr &pShape) const override;
    std::string getName() const override;

  protected:
    MergeShapeWithOffsetStackCommand(Shape::SharedPtr pShape, Vertex offset);

  private:
    Shape::SharedPtr mpShape;
    Vertex mOffset;
};

} // namespace psdf
