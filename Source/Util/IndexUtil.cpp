#include "IndexUtil.h"

using namespace psdf;

size_t IndexUtil::prevIndex(size_t containerSize, size_t index)
{
    return (index - 1 + containerSize) % containerSize;
}

size_t IndexUtil::nextIndex(size_t containerSize, size_t index)
{
    return (index + 1) % containerSize;
}
