#include "Outline.h"

using namespace psdf;

Outline::Outline(Outline::Vertices vertices) : mVertices(std::move(vertices)), mEdges(connectOrderedVertices(mVertices))
{
    FALCOR_ASSERT(mVertices.size() > 2);
}

Outline::Vertices Outline::getVertices() const
{
    return mVertices;
}

Outline::Edges Outline::getEdges() const
{
    return mEdges;
}

Outline::FloatVertices Outline::getFloatVertices() const
{
    FloatVertices vertices;
    vertices.reserve(mVertices.size());
    std::copy(mVertices.cbegin(), mVertices.cend(), std::back_inserter(vertices));
    return vertices;
}

Outline::FloatEdges Outline::getFloatEdges() const
{
    FloatEdges edges;
    edges.reserve(mEdges.size());
    std::transform(mEdges.cbegin(), mEdges.cend(), std::back_inserter(edges), [](const Edge &segment) {
        return std::array<float2, 2>{{segment.getVertex1(), segment.getVertex2()}};
    });
    return edges;
}

Outline::Edges Outline::connectOrderedVertices(const std::vector<Vertex> &vertices)
{
    std::vector<Edge> edges;
    edges.reserve(vertices.size());

    for (int32_t i = 0; i < vertices.size(); i++)
    {
        edges.emplace_back(Edge{{vertices[i], vertices[(i + 1) % vertices.size()]}});
    }

    return edges;
}
