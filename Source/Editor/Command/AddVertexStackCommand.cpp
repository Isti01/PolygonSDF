#include "AddVertexStackCommand.h"

using namespace psdf;

StackCommand::SharedPtr AddVertexStackCommand::create(size_t outlineIndex, const Vertex &vertex)
{
    return SharedPtr(new AddVertexStackCommand(outlineIndex, vertex));
}

AddVertexStackCommand::AddVertexStackCommand(size_t outlineIndex, const Vertex &vertex)
    : mOutlineIndex(outlineIndex), mVertex(vertex)
{
}

Shape::SharedPtr AddVertexStackCommand::perform(const Shape::SharedPtr &pShape) const
{
    auto outlinesCopy = pShape->getOutlines();
    auto verticesCopy = outlinesCopy[mOutlineIndex].getVertices();
    verticesCopy.emplace_back(mVertex);
    outlinesCopy[mOutlineIndex] = Outline(verticesCopy);
    return Shape::create(outlinesCopy);
}

std::string AddVertexStackCommand::getName() const
{
    return "AddVertexStackCommand";
}

Vertex AddVertexStackCommand::getVertex()
{
    return mVertex;
}
