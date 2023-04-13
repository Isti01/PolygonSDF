#pragma once

#include "StackCommand.h"

namespace psdf
{

class InsertPointStackCommand : public StackCommand
{
  public:
    using SharedPtr = std::shared_ptr<InsertPointStackCommand>;
    static SharedPtr create(size_t groupIndex, size_t vertexIndex, Point point);

    Polygon::SharedPtr perform(const Polygon::SharedPtr &pPolygon) const override;
    std::string getName() const override;
    size_t getGroupIndex() const;
    size_t getIndex() const;
    Point getPoint() const;

  protected:
    InsertPointStackCommand(size_t groupIndex, size_t vertexIndex, Point point);

  private:
    size_t mGroupIndex;
    size_t mVertexIndex;
    Point mPoint;
};

} // namespace psdf
