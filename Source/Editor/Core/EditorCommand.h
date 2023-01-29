#pragma once

#include <memory>
#include <string>

namespace psdf
{

class EditorCommand
{
  public:
    using SharedPtr = std::shared_ptr<EditorCommand>;

    [[nodiscard]] virtual std::string getName() const = 0;

    virtual ~EditorCommand() = default;
};

} // namespace psdf
