#include "DeleteOutlineStackCommand.h"

using namespace psdf;

DeleteOutlineStackCommand::SharedPtr DeleteOutlineStackCommand::create(size_t outlineIndex)
{
    return SharedPtr(new DeleteOutlineStackCommand(outlineIndex));
}

DeleteOutlineStackCommand::DeleteOutlineStackCommand(size_t outlineIndex) : mOutlineIndex(outlineIndex)
{
}

Shape::SharedPtr DeleteOutlineStackCommand::perform(const Shape::SharedPtr &pShape) const
{
    auto outlinesCopy = pShape->getOutlines();
    outlinesCopy.erase(outlinesCopy.begin() + static_cast<long long>(mOutlineIndex));
    return Shape::create(outlinesCopy);
}

std::string DeleteOutlineStackCommand::getName() const
{
    return "DeleteOutlineStackCommand";
}
