#pragma once

#include <memory>

namespace psdf
{

class EditorCommand
{
  public:
    using SharedPtr = std::shared_ptr<EditorCommand>;

  protected:
    EditorCommand() = default;
};

} // namespace psdf
