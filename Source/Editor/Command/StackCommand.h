#pragma once

#include "../../Polygon/Polygon.h"
#include "../Core/EditorCommand.h"

namespace psdf
{

class StackCommand : public EditorCommand
{
  public:
    using SharedPtr = std::shared_ptr<StackCommand>;

    virtual Polygon::SharedPtr perform(const Polygon::SharedPtr &polygon) const = 0;
};

} // namespace psdf
