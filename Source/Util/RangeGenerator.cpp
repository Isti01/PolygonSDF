#include "RangeGenerator.h"

psdf::RangeGenerator::RangeGenerator(int32_t start, int32_t step) : mCurrent(start), mStep(step)
{
}

int32_t psdf::RangeGenerator::operator()()
{
    int32_t toReturn = mCurrent;
    mCurrent += mStep;
    return toReturn;
}
