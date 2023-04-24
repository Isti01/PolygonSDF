#pragma once

#include "StackCommand.h"

namespace psdf
{

class MergePolygonWithOffsetStackCommand : public StackCommand
{
  public:
    using SharedPtr = std::shared_ptr<MergePolygonWithOffsetStackCommand>;
    static SharedPtr create(Polygon::SharedPtr pPolygon, Point offset);

    Polygon::SharedPtr perform(const Polygon::SharedPtr &polygon) const override;
    std::string getName() const override;

  protected:
    MergePolygonWithOffsetStackCommand(Polygon::SharedPtr pPolygon, Point offset);

  private:
    Polygon::SharedPtr mpPolygon;
    Point mOffset;
};

} // namespace psdf
