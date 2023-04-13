#include "AddPointStackCommand.h"

using namespace psdf;

StackCommand::SharedPtr AddPointStackCommand::create(size_t groupIndex, const Point &point)
{
    return SharedPtr(new AddPointStackCommand(groupIndex, point));
}

AddPointStackCommand::AddPointStackCommand(size_t groupIndex, const Point &point)
    : mGroupIndex(groupIndex), mPoint(point)
{
}

Polygon::SharedPtr AddPointStackCommand::perform(const Polygon::SharedPtr &pPolygon) const
{
    auto polygonsCopy = pPolygon->getPolygons();
    auto groupPointsCopy = polygonsCopy[mGroupIndex].getPoints();
    groupPointsCopy.emplace_back(mPoint);
    polygonsCopy[mGroupIndex] = SubPolygon(groupPointsCopy);
    return Polygon::create(polygonsCopy);
}

std::string AddPointStackCommand::getName() const
{
    return "AddPointStackCommand";
}

Point AddPointStackCommand::getPoint()
{
    return mPoint;
}
