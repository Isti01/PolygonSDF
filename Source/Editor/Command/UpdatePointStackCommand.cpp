#include "UpdatePointStackCommand.h"

using namespace psdf;

StackCommand::SharedPtr UpdatePointStackCommand::create(size_t index, const Point &point)
{
    return StackCommand::SharedPtr(new UpdatePointStackCommand(index, point));
}

UpdatePointStackCommand::UpdatePointStackCommand(size_t index, const Point &point) : mIndex(index), mPoint(point)
{
}

Polygon::SharedPtr UpdatePointStackCommand::perform(const Polygon::SharedPtr &pPolygon) const
{
    auto pointsCopy = pPolygon->getPoints();
    pointsCopy[mIndex] = mPoint;
    return Polygon::create(pointsCopy);
}

bool UpdatePointStackCommand::canMerge(const StackCommand::SharedPtr &pCommand) const
{
    auto updateCommand = std::dynamic_pointer_cast<UpdatePointStackCommand>(pCommand);
    if (updateCommand == nullptr)
    {
        return false;
    }

    return updateCommand->getIndex() == getIndex();
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
