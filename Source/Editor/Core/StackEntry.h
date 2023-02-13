#pragma once

#include "../../Polygon/Polygon.h"
#include "../Command/StackCommand.h"

namespace psdf
{

struct StackEntry
{
    static const StackEntry kEmptyStackEntry;

    StackCommand::SharedPtr command;
    Polygon::SharedPtr polygon;
};

} // namespace psdf
