#include "UpdateVertexStackCommand.h"

using namespace psdf;

StackCommand::SharedPtr UpdateVertexStackCommand::create(size_t outlineIndex, size_t vertexIndex, const Vertex &vertex)
{
    return StackCommand::SharedPtr(new UpdateVertexStackCommand(outlineIndex, vertexIndex, vertex));
}

UpdateVertexStackCommand::UpdateVertexStackCommand(size_t outlineIndex, size_t vertexIndex, const Vertex &vertex)
    : mOutlineIndex(outlineIndex), mVertexIndex(vertexIndex), mVertex(vertex)
{
}

Shape::SharedPtr UpdateVertexStackCommand::perform(const Shape::SharedPtr &pShape) const
{
    auto outlineCopy = pShape->getOutlines();
    auto verticesCopy = outlineCopy[mOutlineIndex].getVertices();
    verticesCopy[mVertexIndex] = mVertex;
    outlineCopy[mOutlineIndex] = Outline(verticesCopy);
    return Shape::create(outlineCopy);
}

bool UpdateVertexStackCommand::canMerge(const StackCommand::SharedPtr &pCommand) const
{
    auto updateCommand = std::dynamic_pointer_cast<UpdateVertexStackCommand>(pCommand);
    if (updateCommand == nullptr)
    {
        return false;
    }

    return updateCommand->getOutlineIndex() == getOutlineIndex() && updateCommand->getVertexIndex() == getVertexIndex();
}

std::string UpdateVertexStackCommand::getName() const
{
    return "UpdateVertexStackCommand";
}

size_t UpdateVertexStackCommand::getOutlineIndex() const
{
    return mOutlineIndex;
}

size_t UpdateVertexStackCommand::getVertexIndex() const
{
    return mVertexIndex;
}

Vertex UpdateVertexStackCommand::getVertex() const
{
    return mVertex;
}
