#include "AddNewOutlineStackCommand.h"

using namespace psdf;

AddNewOutlineStackCommand::SharedPtr AddNewOutlineStackCommand::create(Outline newOutline)
{
    return SharedPtr(new AddNewOutlineStackCommand(std::move(newOutline)));
}

AddNewOutlineStackCommand::AddNewOutlineStackCommand(Outline newOutline) : mNewOutline(std::move(newOutline))
{
}

Shape::SharedPtr AddNewOutlineStackCommand::perform(const Shape::SharedPtr &polygon) const
{
    std::vector<Outline> outlineCopy = polygon->getOutlines();
    outlineCopy.push_back(mNewOutline);
    return Shape::create(outlineCopy);
}

std::string AddNewOutlineStackCommand::getName() const
{
    return "AddNewOutlineStackCommand";
}
