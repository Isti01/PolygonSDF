#include "AddPointStackCommand.h"

using namespace psdf;

StackCommand::SharedPtr AddPointStackCommand::create(const float2 &point)
{
    return SharedPtr(new AddPointStackCommand(point));
}

AddPointStackCommand::AddPointStackCommand(const float2 &point) : mPoint(point)
{
}

Polygon::SharedPtr AddPointStackCommand::perform(const Polygon::SharedPtr &polygon) const
{
    auto pointsCopy = polygon->getPoints();
    pointsCopy.emplace_back(mPoint);
    return Polygon::create(pointsCopy);
}

std::string AddPointStackCommand::getName() const
{
    return "AddPointStackCommand";
}

float2 AddPointStackCommand::getPoint()
{
    return mPoint;
}
