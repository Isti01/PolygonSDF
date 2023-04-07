#include "SdfPlaneAlgorithm.h"

using namespace psdf;

SdfPlaneAlgorithmOutput::SharedPtr SdfPlaneAlgorithm::calculateForPolygon(const Polygon::SharedPtr &pPolygon)
{
    std::vector<Segment> segments = pPolygon->getSegments();

    std::vector<LineRegion> lineRegions;
    lineRegions.reserve(segments.size());

    std::vector<PointRegion> pointRegions;
    pointRegions.reserve(segments.size());

    size_t size = segments.size();
    for (int i = 0; i < size; i++)
    {
        Segment segment1 = segments[i];
        Segment segment2 = segments[(i + 1) % size];

        glm::dvec2 edgeVector1 = segment1.getEdgeVector();
        glm::dvec2 edgeVector2 = segment2.getEdgeVector();
        double cornerSign = glm::sign(glm::dot(glm::dvec2{-edgeVector1.y, edgeVector1.x}, edgeVector2));

        lineRegions.emplace_back(segment1);
        lineRegions[i].polyCut({segment1.getPoint2(), segment1.getPoint1()}, {edgeVector1, -edgeVector1});
        pointRegions.emplace_back(segment1.getPoint2(), cornerSign);
        pointRegions[i].polyCut({segment1.getPoint2(), segment1.getPoint2()}, {edgeVector2, -edgeVector1});
    }

    PointRegion::cutWithPoints(pointRegions);
    PointRegion::cutWithLines(pointRegions, lineRegions);

    LineRegion::cutWithPoints(lineRegions, pointRegions);
    LineRegion::cutWithLines(lineRegions);

    return SdfPlaneAlgorithmOutput::create(pointRegions, lineRegions);
}
