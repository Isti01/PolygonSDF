#pragma once

#include <memory>
#include <string>

namespace psdf
{

class EditorEvent
{
  public:
    using SharedPtr = std::shared_ptr<EditorEvent>;

    virtual std::string getName() const = 0;
    virtual ~EditorEvent() = default;
};

} // namespace psdf
