#pragma once

#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

class RangeGenerator
{
  public:
    RangeGenerator(int32_t start = 0, int32_t step = 1);

    int32_t operator()();

  private:
    int32_t mCurrent;
    int32_t mStep;
};

} // namespace psdf
