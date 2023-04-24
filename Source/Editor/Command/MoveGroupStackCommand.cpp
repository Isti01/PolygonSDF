#include "MoveGroupStackCommand.h"

using namespace psdf;

MoveGroupStackCommand::SharedPtr MoveGroupStackCommand::create(size_t groupIndex, Point from, Point to)
{
    return SharedPtr(new MoveGroupStackCommand(groupIndex, from, to));
}

MoveGroupStackCommand::MoveGroupStackCommand(size_t groupIndex, Point from, Point to)
    : mGroupIndex(groupIndex), mFrom(from), mTo(to)
{
}

Polygon::SharedPtr MoveGroupStackCommand::perform(const Polygon::SharedPtr &pPolygon) const
{
    auto polygonsCopy = pPolygon->getPolygons();
    auto pointsCopy = polygonsCopy[mGroupIndex].getPoints();
    auto offset = mTo - mFrom;
    for (auto &point : pointsCopy)
    {
        point += offset;
    }
    polygonsCopy[mGroupIndex] = pointsCopy;
    return Polygon::create(polygonsCopy);
}

std::string MoveGroupStackCommand::getName() const
{
    return "MoveGroupStackCommand";
}

bool MoveGroupStackCommand::canMerge(const StackCommand::SharedPtr &pCommand) const
{
    auto moveCommand = std::dynamic_pointer_cast<MoveGroupStackCommand>(pCommand);
    if (moveCommand == nullptr)
    {
        return false;
    }

    return moveCommand->getGroupIndex() == getGroupIndex() && moveCommand->getTo() == getFrom();
}

StackCommand::SharedPtr MoveGroupStackCommand::merge(const StackCommand::SharedPtr &pOther)
{
    auto moveCommand = std::dynamic_pointer_cast<MoveGroupStackCommand>(pOther);
    if (moveCommand == nullptr)
    {
        return StackCommand::merge(pOther);
    }
    return MoveGroupStackCommand::create(getGroupIndex(), moveCommand->getTo(), getTo());
}

size_t MoveGroupStackCommand::getGroupIndex() const
{
    return mGroupIndex;
}

Point MoveGroupStackCommand::getFrom() const
{
    return mFrom;
}

Point MoveGroupStackCommand::getTo() const
{
    return mTo;
}
