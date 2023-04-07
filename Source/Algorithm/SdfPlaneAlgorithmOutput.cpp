#include "SdfPlaneAlgorithmOutput.h"

using namespace psdf;

SdfPlaneAlgorithmOutput::SharedPtr SdfPlaneAlgorithmOutput::create(std::vector<PointRegion> pointRegions,
                                                                   std::vector<LineRegion> lineRegions)
{
    return SharedPtr(new SdfPlaneAlgorithmOutput(std::move(pointRegions), std::move(lineRegions)));
}

std::vector<PointRegion> SdfPlaneAlgorithmOutput::getPointRegions() const
{
    return mPointRegions;
}

std::vector<LineRegion> SdfPlaneAlgorithmOutput::getLineRegions() const
{
    return mLineRegions;
}

SdfPlaneAlgorithmOutput::SdfPlaneAlgorithmOutput(std::vector<PointRegion> pointRegions,
                                                 std::vector<LineRegion> lineRegions)
    : mPointRegions(std::move(pointRegions)), mLineRegions(std::move(lineRegions))
{
}
