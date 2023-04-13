#include "UpdatePointStackCommand.h"

using namespace psdf;

StackCommand::SharedPtr UpdatePointStackCommand::create(size_t groupIndex, size_t vertexIndex, const Point &point)
{
    return StackCommand::SharedPtr(new UpdatePointStackCommand(groupIndex, vertexIndex, point));
}

UpdatePointStackCommand::UpdatePointStackCommand(size_t groupIndex, size_t vertexIndex, const Point &point)
    : mGroupIndex(groupIndex), mVertexIndex(vertexIndex), mPoint(point)
{
}

Polygon::SharedPtr UpdatePointStackCommand::perform(const Polygon::SharedPtr &pPolygon) const
{
    auto polygonsCopy = pPolygon->getPolygons();
    auto groupPointsCopy = polygonsCopy[mGroupIndex].getPoints();
    groupPointsCopy[mVertexIndex] = mPoint;
    polygonsCopy[mGroupIndex] = SubPolygon(groupPointsCopy);
    return Polygon::create(polygonsCopy);
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
    return mVertexIndex;
}

Point UpdatePointStackCommand::getPoint() const
{
    return mPoint;
}
