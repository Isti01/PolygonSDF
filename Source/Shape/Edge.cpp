#include "Edge.h"
#include "../CommonConstants.h"

using namespace psdf;

Edge::Edge(const Edge::Endpoints &endpoints) : mEndpoints(endpoints)
{
}

Edge::Endpoints Edge::getEndpoints() const
{
    return mEndpoints;
}

glm::dvec2 Edge::getEdgeVector() const
{
    return mEndpoints[1] - mEndpoints[0];
}

Vertex Edge::getVertex1() const
{
    return mEndpoints[0];
}

Vertex Edge::getVertex2() const
{
    return mEndpoints[1];
}

static bool isIntersecting(const Edge &s1, const Edge &s2)
{
    glm::dvec2 v1 = s1.getVertex1() - s2.getVertex1();
    glm::dvec2 v2 = s2.getEdgeVector();
    glm::dvec2 v3(-s1.getEdgeVector().y, s1.getEdgeVector().x);
    double d = glm::dot(v2, v3);
    if (glm::abs(d) < CommonConstants::kEpsilon)
    {
        return false;
    }
    double t = glm::dot(v1, v3) / d;
    return t >= 0.0 && t <= 1.0;
}

bool Edge::isIntersecting(const Edge &other) const
{
    return ::isIntersecting(other, *this) && ::isIntersecting(*this, other);
}
