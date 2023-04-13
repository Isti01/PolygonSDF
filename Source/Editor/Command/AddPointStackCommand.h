#pragma once

#include "../Core/EditorCommand.h"
#include "StackCommand.h"
#include "Utils/Math/Vector.h"

namespace psdf
{
using namespace Falcor;

class AddPointStackCommand : public StackCommand
{
  public:
    static StackCommand::SharedPtr create(size_t groupIndex, const Point &point);

    Polygon::SharedPtr perform(const Polygon::SharedPtr &pPolygon) const override;

    std::string getName() const override;

    [[nodiscard]] Point getPoint();

  protected:
    AddPointStackCommand(size_t groupIndex, const Point &point);

  private:
    size_t mGroupIndex;
    Point mPoint;
};

}; // namespace psdf
