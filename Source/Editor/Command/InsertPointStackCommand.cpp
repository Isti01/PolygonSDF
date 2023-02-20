#include "InsertPointStackCommand.h"

using namespace psdf;

InsertPointStackCommand::SharedPtr InsertPointStackCommand::create(size_t index, Point point)
{
    return SharedPtr(new InsertPointStackCommand(index, point));
}

InsertPointStackCommand::InsertPointStackCommand(size_t index, Point point) : mIndex(index), mPoint(point)
{
}

Polygon::SharedPtr InsertPointStackCommand::perform(const Polygon::SharedPtr &polygon) const
{
    auto points = polygon->getPoints();
    points.insert(points.begin() + mIndex, mPoint);
    return Polygon::create(points);
}

std::string InsertPointStackCommand::getName() const
{
    return "InsertPointStackCommand";
}

size_t InsertPointStackCommand::getIndex() const
{
    return mIndex;
}

 Point InsertPointStackCommand::getPoint() const
{
    return mPoint;
}
