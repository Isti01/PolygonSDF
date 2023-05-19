#include "DeleteVertexStackCommand.h"

using namespace psdf;

StackCommand::SharedPtr DeleteVertexStackCommand::create(size_t outlineIndex, size_t vertexIndex)
{
    return StackCommand::SharedPtr(new DeleteVertexStackCommand(outlineIndex, vertexIndex));
}

DeleteVertexStackCommand::DeleteVertexStackCommand(size_t outlineIndex, size_t vertexIndex)
    : mOutlineIndex(outlineIndex), mVertexIndex(vertexIndex)
{
}

Shape::SharedPtr DeleteVertexStackCommand::perform(const Shape::SharedPtr &pShape) const
{
    auto outlinesCopy = pShape->getOutlines();
    auto verticesCopy = outlinesCopy[mOutlineIndex].getVertices();
    verticesCopy.erase(verticesCopy.begin() + static_cast<long long>(mVertexIndex));
    outlinesCopy[mOutlineIndex] = Outline(verticesCopy);
    return Shape::create(outlinesCopy);
}

std::string DeleteVertexStackCommand::getName() const
{
    return "DeleteVertexStackCommand";
}

size_t DeleteVertexStackCommand::getOutlineIndex() const
{
    return mOutlineIndex;
}

size_t DeleteVertexStackCommand::getVertexIndex() const
{
    return mVertexIndex;
}
