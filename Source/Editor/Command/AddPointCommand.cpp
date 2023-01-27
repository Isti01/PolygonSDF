#include "AddPointCommand.h"

using namespace psdf;

EditorCommand::SharedPtr AddPointCommand::create(const float2 &point)
{
    return SharedPtr(new AddPointCommand(point));
}

AddPointCommand::AddPointCommand(const float2 &point) : mPoint(point)
{
}

float2 AddPointCommand::getPoint()
{
    return mPoint;
}
