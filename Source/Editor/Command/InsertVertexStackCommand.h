#pragma once

#include "StackCommand.h"

namespace psdf
{

class InsertVertexStackCommand : public StackCommand
{
  public:
    using SharedPtr = std::shared_ptr<InsertVertexStackCommand>;
    static SharedPtr create(size_t groupIndex, size_t vertexIndex, Vertex vertex);

    Shape::SharedPtr perform(const Shape::SharedPtr &pShape) const override;
    std::string getName() const override;
    size_t getOutlineIndex() const;
    size_t getVertexIndex() const;
    Vertex getVertex() const;

  protected:
    InsertVertexStackCommand(size_t groupIndex, size_t vertexIndex, Vertex vertex);

  private:
    size_t mOutlineIndex;
    size_t mVertexIndex;
    Vertex mVertex;
};

} // namespace psdf
