#include "InsertPointStackCommand.h"

using namespace psdf;

InsertPointStackCommand::SharedPtr InsertPointStackCommand::create(size_t groupIndex, size_t vertexIndex, Point point)
{
    return SharedPtr(new InsertPointStackCommand(groupIndex, vertexIndex, point));
}

InsertPointStackCommand::InsertPointStackCommand(size_t groupIndex, size_t vertexIndex, Point point)
    : mGroupIndex(groupIndex), mVertexIndex(vertexIndex), mPoint(point)
{
}

Polygon::SharedPtr InsertPointStackCommand::perform(const Polygon::SharedPtr &pPolygon) const
{
    auto polygonsCopy = pPolygon->getPolygons();
    auto groupPointsCopy = polygonsCopy[mGroupIndex].getPoints();
    groupPointsCopy.insert(groupPointsCopy.begin() + mVertexIndex, mPoint);
    polygonsCopy[mGroupIndex] = SubPolygon(groupPointsCopy);
    return Polygon::create(polygonsCopy);
}

std::string InsertPointStackCommand::getName() const
{
    return "InsertPointStackCommand";
}

size_t InsertPointStackCommand::getGroupIndex() const
{
    return mGroupIndex;
}

size_t InsertPointStackCommand::getIndex() const
{
    return mVertexIndex;
}

Point InsertPointStackCommand::getPoint() const
{
    return mPoint;
}
