#pragma once

#include "Edge.h"
#include "Vertex.h"
#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

class Outline
{
  public:
    using Vertices = std::vector<Vertex>;
    using Edges = std::vector<Edge>;

    using FloatVertices = std::vector<float2>;
    using FloatEdges = std::vector<std::array<float2, 2>>;

    Outline(Vertices vertices);

    Vertices getVertices() const;
    Edges getEdges() const;

    FloatVertices getFloatVertices() const;
    FloatEdges getFloatEdges() const;

  private:
    static Edges connectOrderedVertices(const std::vector<Vertex> &vertices);

  private:
    Vertices mVertices;
    Edges mEdges;
};

} // namespace psdf
