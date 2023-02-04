#include "UpdatePointStackCommand.h"

using namespace psdf;

StackCommand::SharedPtr UpdatePointStackCommand::create(size_t index, const Point &point)
{
    return StackCommand::SharedPtr(new UpdatePointStackCommand(index, point));
}

UpdatePointStackCommand::UpdatePointStackCommand(size_t index, const Point &point) : mIndex(index), mPoint(point)
{
}

Polygon::SharedPtr UpdatePointStackCommand::perform(const Polygon::SharedPtr &polygon) const
{
    auto pointsCopy = polygon->getPoints();
    pointsCopy[mIndex] = mPoint;
    return Polygon::create(pointsCopy);
}

std::string UpdatePointStackCommand::getName() const
{
    return "UpdatePointStackCommand";
}

size_t UpdatePointStackCommand::getIndex() const
{
    return mIndex;
}

Point UpdatePointStackCommand::getPoint() const
{
    return mPoint;
}
