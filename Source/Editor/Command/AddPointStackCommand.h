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
    static StackCommand::SharedPtr create(const float2 &point);

    Polygon::SharedPtr perform(const Polygon::SharedPtr &polygon) const override;

    std::string getName() const override;

    [[nodiscard]] float2 getPoint();

  protected:
    AddPointStackCommand(const float2 &point);

  private:
    float2 mPoint;
};

}; // namespace psdf
