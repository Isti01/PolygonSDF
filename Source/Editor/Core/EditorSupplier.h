#pragma once

#include "EditorCommand.h"
#include <memory>

namespace psdf
{

class EditorSupplier
{
  public:
    using SharedPtr = std::shared_ptr<EditorSupplier>;

    virtual EditorCommand::SharedPtr get() = 0;
};

} // namespace psdf
