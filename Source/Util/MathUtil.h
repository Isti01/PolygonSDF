#pragma once

#include <array>

namespace psdf
{

class MathUtil
{
  public:
    static bool equalsEpsilon(double value1, double value2, double epsilon)
    {
        return glm::abs(value1 - value2) < epsilon;
    }

    template <typename T, size_t N>
    static bool isMonotonic(const std::array<T, N> &values, T epsilon)
    {
        bool isMonotonic = true;
        for (size_t i = 1; i < values.size(); i++)
        {
            if (!equalsEpsilon(values[i - 1], values[i], epsilon) && values[i - 1] > values[i])
            {
                isMonotonic = false;
                break;
            }
        }
        if (isMonotonic)
        {
            return true;
        }
        isMonotonic = true;
        for (size_t i = 1; i < values.size(); i++)
        {
            if (!equalsEpsilon(values[i - 1], values[i], epsilon) && values[i - 1] < values[i])
            {
                isMonotonic = false;
                break;
            }
        }
        return isMonotonic;
    }

  private:
    MathUtil() = default;
};

} // namespace psdf
