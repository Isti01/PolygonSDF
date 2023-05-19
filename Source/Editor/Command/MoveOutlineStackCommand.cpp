#include "MoveOutlineStackCommand.h"

using namespace psdf;

MoveOutlineStackCommand::SharedPtr MoveOutlineStackCommand::create(size_t outlineIndex, Vertex from, Vertex to)
{
    return SharedPtr(new MoveOutlineStackCommand(outlineIndex, from, to));
}

MoveOutlineStackCommand::MoveOutlineStackCommand(size_t outlineIndex, Vertex from, Vertex to)
    : mOutlineIndex(outlineIndex), mFrom(from), mTo(to)
{
}

Shape::SharedPtr MoveOutlineStackCommand::perform(const Shape::SharedPtr &pShape) const
{
    auto outlinesCopy = pShape->getOutlines();
    auto verticesCopy = outlinesCopy[mOutlineIndex].getVertices();
    auto offset = mTo - mFrom;
    for (auto &point : verticesCopy)
    {
        point += offset;
    }
    outlinesCopy[mOutlineIndex] = verticesCopy;
    return Shape::create(outlinesCopy);
}

std::string MoveOutlineStackCommand::getName() const
{
    return "MoveOutlineStackCommand";
}

bool MoveOutlineStackCommand::canMerge(const StackCommand::SharedPtr &pCommand) const
{
    auto moveCommand = std::dynamic_pointer_cast<MoveOutlineStackCommand>(pCommand);
    if (moveCommand == nullptr)
    {
        return false;
    }

    return moveCommand->getOutlineIndex() == getOutlineIndex() && moveCommand->getTo() == getFrom();
}

StackCommand::SharedPtr MoveOutlineStackCommand::merge(const StackCommand::SharedPtr &pOther)
{
    auto moveCommand = std::dynamic_pointer_cast<MoveOutlineStackCommand>(pOther);
    if (moveCommand == nullptr)
    {
        return StackCommand::merge(pOther);
    }
    return MoveOutlineStackCommand::create(getOutlineIndex(), moveCommand->getTo(), getTo());
}

size_t MoveOutlineStackCommand::getOutlineIndex() const
{
    return mOutlineIndex;
}

Vertex MoveOutlineStackCommand::getFrom() const
{
    return mFrom;
}

Vertex MoveOutlineStackCommand::getTo() const
{
    return mTo;
}
