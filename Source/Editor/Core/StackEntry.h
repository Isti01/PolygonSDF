#pragma once

#include "../../Shape/Shape.h"
#include "../Command/StackCommand.h"

namespace psdf
{

struct StackEntry
{
    static const StackEntry kEmptyStackEntry;

    StackCommand::SharedPtr pCommand;
    Shape::SharedPtr pShape;
};

} // namespace psdf
