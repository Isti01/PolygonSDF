#pragma once

#include "../../Polygon/Polygon.h"
#include "EditorCommand.h"

namespace psdf
{

struct StackEntry
{
    EditorCommand::SharedPtr command;
    Polygon::SharedPtr polygon;
};

} // namespace psdf
