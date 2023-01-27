#pragma once

#include "../Core/EditorCommand.h"
#include "Utils/Math/Vector.h"

namespace psdf
{
using namespace Falcor;

class AddPointCommand : public EditorCommand
{
  public:
    static EditorCommand::SharedPtr create(const float2 &point);

    [[nodiscard]] float2 getPoint();

  protected:
    AddPointCommand(const float2 &point);

  private:
    float2 mPoint;
};

}; // namespace psdf
