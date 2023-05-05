#include "CalculateSdfPlaneAlgorithmCommand.h"

using namespace psdf;

CalculateSdfPlaneAlgorithmCommand::SharedPtr CalculateSdfPlaneAlgorithmCommand::create(
    SdfPlaneAlgorithmExecutionDesc executionDesc)
{
    return SharedPtr(new CalculateSdfPlaneAlgorithmCommand(executionDesc));
}

CalculateSdfPlaneAlgorithmCommand::CalculateSdfPlaneAlgorithmCommand(SdfPlaneAlgorithmExecutionDesc executionDesc)
    : mExecutionDesc(executionDesc)
{
}

std::string CalculateSdfPlaneAlgorithmCommand::getName() const
{
    return "CalculateSdfPlaneAlgorithmCommand";
}

Polygon::SharedPtr CalculateSdfPlaneAlgorithmCommand::perform(const Polygon::SharedPtr &polygon) const
{
    auto newPolygon = Polygon::create(polygon->getPolygons());
    newPolygon->runAlgorithm(mExecutionDesc);
    return newPolygon;
}

SdfPlaneAlgorithmExecutionDesc CalculateSdfPlaneAlgorithmCommand::getExecutionDesc() const
{
    return mExecutionDesc;
}
