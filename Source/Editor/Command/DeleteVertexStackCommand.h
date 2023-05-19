#pragma once

#include "StackCommand.h"

namespace psdf
{

class DeleteVertexStackCommand : public StackCommand
{
  public:
    static StackCommand::SharedPtr create(size_t outlineIndex, size_t vertexIndex);

    Shape::SharedPtr perform(const Shape::SharedPtr &pShape) const override;
    std::string getName() const override;

    size_t getOutlineIndex() const;
    size_t getVertexIndex() const;

  protected:
    DeleteVertexStackCommand(size_t outlineIndex, size_t vertexIndex);

  private:
    size_t mOutlineIndex;
    size_t mVertexIndex;
};

} // namespace psdf
