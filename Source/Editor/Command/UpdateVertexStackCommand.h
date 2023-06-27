#pragma once

#include "StackCommand.h"

namespace psdf
{

class UpdateVertexStackCommand : public StackCommand
{
  public:
    static StackCommand::SharedPtr create(size_t outlineIndex, size_t vertexIndex, const Vertex &point);

    Shape::SharedPtr perform(const Shape::SharedPtr &pPolygon) const override;
    bool canMerge(const StackCommand::SharedPtr &pCommand) const override;
    std::string getName() const override;

    size_t getOutlineIndex() const;
    size_t getVertexIndex() const;
    Vertex getVertex() const;

  protected:
    UpdateVertexStackCommand(size_t groupIndex, size_t vertexIndex, const Vertex &point);

  private:
    size_t mOutlineIndex;
    size_t mVertexIndex;
    Vertex mVertex;
};

} // namespace psdf
