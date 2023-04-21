#include "AddNewGroupStackCommand.h"

using namespace psdf;

AddNewGroupStackCommand::SharedPtr AddNewGroupStackCommand::create(SubPolygon newGroup)
{
    return SharedPtr(new AddNewGroupStackCommand(std::move(newGroup)));
}

AddNewGroupStackCommand::AddNewGroupStackCommand(SubPolygon newGroup) : mNewGroup(std::move(newGroup))
{
}

Polygon::SharedPtr AddNewGroupStackCommand::perform(const Polygon::SharedPtr &polygon) const
{
    std::vector<SubPolygon> groupsCopy = polygon->getPolygons();
    groupsCopy.push_back(mNewGroup);
    return Polygon::create(groupsCopy);
}

std::string AddNewGroupStackCommand::getName() const
{
    return "AddNewGroupStackCommand";
}
