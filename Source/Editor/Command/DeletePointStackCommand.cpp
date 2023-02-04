#include "DeletePointStackCommand.h"

using namespace psdf;

StackCommand::SharedPtr DeletePointStackCommand::create(size_t index)
{
    return StackCommand::SharedPtr(new DeletePointStackCommand(index));
}

DeletePointStackCommand::DeletePointStackCommand(size_t index) : mIndex(index)
{
}

Polygon::SharedPtr DeletePointStackCommand::perform(const Polygon::SharedPtr &polygon) const
{
    auto pointsCopy = polygon->getPoints();
    pointsCopy.erase(pointsCopy.begin() + static_cast<long long>(mIndex));
    return Polygon::create(pointsCopy);
}

std::string DeletePointStackCommand::getName() const
{
    return "DeletePointStackCommand";
}
