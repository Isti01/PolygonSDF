#pragma once

#include "EditorEvent.h"
#include <memory>

namespace psdf
{

class EditorConsumer
{
  public:
    using SharedPtr = std::shared_ptr<EditorConsumer>;

    virtual void accept(const EditorEvent::SharedPtr &pEvent) = 0;

    virtual ~EditorConsumer() = default;
};

} // namespace psdf
