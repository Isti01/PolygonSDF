#pragma once

#include "StackCommand.h"

namespace psdf
{

class DeletePointStackCommand : public StackCommand
{
  public:
    static StackCommand::SharedPtr create(size_t groupIndex, size_t vertexIndex);

    Polygon::SharedPtr perform(const Polygon::SharedPtr &pPolygon) const override;
    std::string getName() const override;

    size_t getGroupIndex() const;
    size_t getVertexIndex() const;

  protected:
    DeletePointStackCommand(size_t groupIndex, size_t vertexIndex);

  private:
    size_t mGroupIndex;
    size_t mVertexIndex;
};

} // namespace psdf
