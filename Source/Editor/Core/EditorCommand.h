#pragma once

#include <memory>

namespace psdf
{

class EditorCommand
{
  public:
    using SharedPtr = std::shared_ptr<EditorCommand>;

    virtual ~EditorCommand() = default;

  protected:
    EditorCommand() = default;
};

} // namespace psdf
