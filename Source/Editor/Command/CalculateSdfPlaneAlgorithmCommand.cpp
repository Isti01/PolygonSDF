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

Shape::SharedPtr CalculateSdfPlaneAlgorithmCommand::perform(const Shape::SharedPtr &pShape) const
{
    auto newPolygon = Shape::create(pShape->getOutlines());
    newPolygon->runAlgorithm(mExecutionDesc);
    return newPolygon;
}

SdfPlaneAlgorithmExecutionDesc CalculateSdfPlaneAlgorithmCommand::getExecutionDesc() const
{
    return mExecutionDesc;
}
