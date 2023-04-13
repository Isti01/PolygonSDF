#include "Polygon.h"
#include "../Algorithm/SdfPlaneAlgorithm.h"

#include <utility>

using namespace psdf;

Polygon::SharedPtr Polygon::kExamplePolygon =
    Polygon::create({Points{{.5, 0}, {0, .5}, {-.5, 0}, {0, -.5}}, Points{{.75, 0}, {0, .75}, {-.75, 0}, {0, -.75}}});

Polygon::SharedPtr Polygon::create(std::vector<SubPolygon> polygons)
{
    return SharedPtr(new Polygon(std::move(polygons)));
}

Polygon::Polygon(std::vector<SubPolygon> polygons) : mPolygons(std::move(polygons))
{
}

std::vector<SubPolygon> Polygon::getPolygons() const
{
    return mPolygons;
}

Polygon::FloatSegments psdf::Polygon::getAllFloatSegments() const
{
    FloatSegments floatSegments;
    for (const auto &mPolygon : mPolygons)
    {
        const auto &subSegments = mPolygon.getFloatSegments();
        std::copy(subSegments.cbegin(), subSegments.cend(), std::back_inserter(floatSegments));
    }
    return floatSegments;
}

Polygon::FloatPoints Polygon::getFloatPoints() const
{
    FloatPoints floatPoints;

    for (size_t i = 0; i < mPolygons.size(); i++)
    {
        const auto &subPolygonPoints = mPolygons[i].getFloatPoints();
        std::copy(subPolygonPoints.cbegin(), subPolygonPoints.cend(), std::back_inserter(floatPoints));
    }

    return floatPoints;
}

Polygon::Segments Polygon::getAllSegments() const
{
    Segments segments;
    for (const auto &mPolygon : mPolygons)
    {
        const auto &subSegments = mPolygon.getSegments();
        std::copy(subSegments.cbegin(), subSegments.cend(), std::back_inserter(segments));
    }

    return segments;
}
SdfPlaneAlgorithmOutput::SharedPtr Polygon::getAlgorithmOutput() const
{
    return mpSdfPlaneAlgorithmOutput;
}
void Polygon::runAlgorithm()
{
    mpSdfPlaneAlgorithmOutput = SdfPlaneAlgorithm::calculateForPolygon(this->shared_from_this());
}
