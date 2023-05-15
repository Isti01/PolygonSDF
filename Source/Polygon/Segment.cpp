#include "Segment.h"
#include "../CommonConstants.h"

using namespace psdf;

Segment::Segment(const Segment::Endpoints &endpoints) : mEndpoints(endpoints)
{
}

Segment::Endpoints Segment::getEndpoints() const
{
    return mEndpoints;
}

glm::dvec2 Segment::getEdgeVector() const
{
    return mEndpoints[1] - mEndpoints[0];
}

Point Segment::getPoint1() const
{
    return mEndpoints[0];
}

Point Segment::getPoint2() const
{
    return mEndpoints[1];
}

static bool isIntersecting(const Segment &s1, const Segment &s2)
{
    glm::dvec2 v1 = s1.getPoint1() - s2.getPoint1();
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

bool Segment::isIntersecting(const Segment &other) const
{
    return ::isIntersecting(other, *this) && ::isIntersecting(*this, other);
}
