#pragma once

#include "Vertex.h"
#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

class Edge
{
  public:
    using Endpoints = std::array<Vertex, 2>;

    Edge(const Endpoints &endpoints);

    Endpoints getEndpoints() const;

    Vertex getVertex1() const;
    Vertex getVertex2() const;

    glm::dvec2 getEdgeVector() const;
    bool isIntersecting(const Edge &other) const;

  private:
    Endpoints mEndpoints;
};

} // namespace psdf
