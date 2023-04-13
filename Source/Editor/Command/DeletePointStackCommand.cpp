#include "DeletePointStackCommand.h"

using namespace psdf;

StackCommand::SharedPtr DeletePointStackCommand::create(size_t groupIndex, size_t vertexIndex)
{
    return StackCommand::SharedPtr(new DeletePointStackCommand(groupIndex, vertexIndex));
}

DeletePointStackCommand::DeletePointStackCommand(size_t groupIndex, size_t vertexIndex)
    : mGroupIndex(groupIndex), mVertexIndex(vertexIndex)
{
}

Polygon::SharedPtr DeletePointStackCommand::perform(const Polygon::SharedPtr &pPolygon) const
{
    auto polygonsCopy = pPolygon->getPolygons();
    auto groupPointsCopy = polygonsCopy[mGroupIndex].getPoints();
    groupPointsCopy.erase(groupPointsCopy.begin() + static_cast<long long>(mVertexIndex));
    polygonsCopy[mGroupIndex] = SubPolygon(groupPointsCopy);
    return Polygon::create(polygonsCopy);
}

std::string DeletePointStackCommand::getName() const
{
    return "DeletePointStackCommand";
}

size_t DeletePointStackCommand::getGroupIndex() const
{
    return mGroupIndex;
}

size_t DeletePointStackCommand::getVertexIndex() const
{
    return mVertexIndex;
}
