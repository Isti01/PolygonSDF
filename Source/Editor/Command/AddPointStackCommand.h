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
    static StackCommand::SharedPtr create(const Point &point);

    Polygon::SharedPtr perform(const Polygon::SharedPtr &polygon) const override;

    std::string getName() const override;

    [[nodiscard]] Point getPoint();

  protected:
    AddPointStackCommand(const Point &point);

  private:
    Point mPoint;
};

}; // namespace psdf
