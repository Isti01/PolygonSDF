#pragma once

#include <memory>

namespace psdf
{

class EditorEvent
{
  public:
    using SharedPtr = std::shared_ptr<EditorEvent>;

    virtual ~EditorEvent() = default;

  protected:
    EditorEvent() = default;
};

} // namespace psdf
