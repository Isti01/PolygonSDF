#include "DeleteGroupStackCommand.h"

using namespace psdf;

DeleteGroupStackCommand::SharedPtr DeleteGroupStackCommand::create(size_t groupIndex)
{
    return SharedPtr(new DeleteGroupStackCommand(groupIndex));
}

DeleteGroupStackCommand::DeleteGroupStackCommand(size_t groupIndex) : mGroupIndex(groupIndex)
{
}

Polygon::SharedPtr DeleteGroupStackCommand::perform(const Polygon::SharedPtr &pPolygon) const
{
    auto polygonsCopy = pPolygon->getPolygons();
    polygonsCopy.erase(polygonsCopy.begin() + static_cast<long long>(mGroupIndex));
    return Polygon::create(polygonsCopy);
}

std::string DeleteGroupStackCommand::getName() const
{
    return "DeleteGroupStackCommand";
}
