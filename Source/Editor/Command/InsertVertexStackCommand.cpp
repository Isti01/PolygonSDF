#include "InsertVertexStackCommand.h"

using namespace psdf;

InsertVertexStackCommand::SharedPtr InsertVertexStackCommand::create(size_t outlineIndex, size_t vertexIndex, Vertex vertex)
{
    return SharedPtr(new InsertVertexStackCommand(outlineIndex, vertexIndex, vertex));
}

InsertVertexStackCommand::InsertVertexStackCommand(size_t outlineIndex, size_t vertexIndex, Vertex vertex)
    : mOutlineIndex(outlineIndex), mVertexIndex(vertexIndex), mVertex(vertex)
{
}

Shape::SharedPtr InsertVertexStackCommand::perform(const Shape::SharedPtr &pShape) const
{
    auto outlinesCopy = pShape->getOutlines();
    auto verticesCopy = outlinesCopy[mOutlineIndex].getVertices();
    verticesCopy.insert(verticesCopy.begin() + mVertexIndex, mVertex);
    outlinesCopy[mOutlineIndex] = Outline(verticesCopy);
    return Shape::create(outlinesCopy);
}

std::string InsertVertexStackCommand::getName() const
{
    return "InsertVertexStackCommand";
}

size_t InsertVertexStackCommand::getOutlineIndex() const
{
    return mOutlineIndex;
}

size_t InsertVertexStackCommand::getVertexIndex() const
{
    return mVertexIndex;
}

Vertex InsertVertexStackCommand::getVertex() const
{
    return mVertex;
}
