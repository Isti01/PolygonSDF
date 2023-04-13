#include "CalculateSdfPlaneAlgorithmCommand.h"

using namespace psdf;

CalculateSdfPlaneAlgorithmCommand::SharedPtr CalculateSdfPlaneAlgorithmCommand::create()
{
    return SharedPtr(new CalculateSdfPlaneAlgorithmCommand());
}

std::string CalculateSdfPlaneAlgorithmCommand::getName() const
{
    return "CalculateSdfPlaneAlgorithmCommand";
}

Polygon::SharedPtr CalculateSdfPlaneAlgorithmCommand::perform(const Polygon::SharedPtr &polygon) const
{
    auto newPolygon = Polygon::create(polygon->getPolygons());
    newPolygon->runAlgorithm();
    return newPolygon;
}
