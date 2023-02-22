#pragma once

namespace psdf
{

class IndexUtil
{
  public:
    static size_t prevIndex(size_t containerSize, size_t index);
    static size_t nextIndex(size_t containerSize, size_t index);

  private:
    IndexUtil() = default;
};

} // namespace psdf
