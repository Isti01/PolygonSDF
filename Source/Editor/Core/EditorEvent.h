#pragma once

#include <memory>

namespace psdf
{

class EditorEvent
{
  public:
    using SharedPtr = std::shared_ptr<EditorEvent>;

  protected:
    EditorEvent() = default;
};

} // namespace psdf
