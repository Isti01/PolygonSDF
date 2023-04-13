#pragma once

#include "StackCommand.h"
namespace psdf
{

class UpdatePointStackCommand : public StackCommand
{
  public:
    static StackCommand::SharedPtr create(size_t groupIndex, size_t vertexIndex, const Point &point);

    Polygon::SharedPtr perform(const Polygon::SharedPtr &pPolygon) const override;
    bool canMerge(const StackCommand::SharedPtr &pCommand) const override;
    std::string getName() const override;

    size_t getIndex() const;
    Point getPoint() const;

  protected:
    UpdatePointStackCommand(size_t groupIndex, size_t vertexIndex, const Point &point);

  private:
    size_t mGroupIndex;
    size_t mVertexIndex;
    Point mPoint;
};

} // namespace psdf
