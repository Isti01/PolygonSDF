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

bool inAABB(const Point &e1, const Point &e2, const Point &p)
{
    return p.x <= glm::max(e1.x, e2.x) && p.x >= glm::min(e1.x, e2.x) && p.y <= glm::max(e1.y, e2.y) &&
           p.y >= glm::min(e1.y, e2.y);
}

double orientation(const Point &p, const Point &q, const Point &r)
{
    double o = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (glm::abs(o) < CommonConstants::kEpsilon)
    {
        return 0;
    }

    return glm::sign(o);
}

bool Segment::isIntersecting(const Segment &other) const
{
    const auto &p1 = getPoint1();
    const auto &e1 = getPoint2();
    const auto &p2 = other.getPoint1();
    const auto &e2 = other.getPoint2();

    double o1 = orientation(p1, e1, p2);
    double o2 = orientation(p1, e1, e2);
    double o3 = orientation(p2, e2, p1);
    double o4 = orientation(p2, e2, e1);

    if (glm::all(glm::notEqual(glm::dvec2{o1, o3}, glm::dvec2{o2, o4}, CommonConstants::kEpsilon)))
    {
        return true;
    }

    if (glm::abs(o1) < CommonConstants::kEpsilon && inAABB(p1, p2, e1))
    {
        return true;
    }

    if (glm::abs(o2) < CommonConstants::kEpsilon && inAABB(p1, e2, e1))
    {
        return true;
    }

    if (glm::abs(o3) < CommonConstants::kEpsilon && inAABB(p2, p1, e2))
    {
        return true;
    }

    if (glm::abs(o4) < CommonConstants::kEpsilon && inAABB(p2, e1, e2))
    {
        return true;
    }

    return false;
}
