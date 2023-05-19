#pragma once

#include "../Core/EditorCommand.h"
#include "StackCommand.h"
#include "Utils/Math/Vector.h"

namespace psdf
{
using namespace Falcor;

class AddVertexStackCommand : public StackCommand
{
  public:
    static StackCommand::SharedPtr create(size_t outlineIndex, const Vertex &vertex);

    Shape::SharedPtr perform(const Shape::SharedPtr &pShape) const override;

    std::string getName() const override;

    [[nodiscard]] Vertex getVertex();

  protected:
    AddVertexStackCommand(size_t outlineIndex, const Vertex &vertex);

  private:
    size_t mOutlineIndex;
    Vertex mVertex;
};

}; // namespace psdf
