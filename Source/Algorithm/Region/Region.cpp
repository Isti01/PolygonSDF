#include "Region.h"

using namespace psdf;

Region::Region() : mBounds(rmcv::mat4x2{-1, -1, 1, -1, 1, 1, -1, 1} * InitialBoundScale)
{
}
