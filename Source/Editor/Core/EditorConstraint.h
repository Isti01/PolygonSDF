#pragma once

#include "EditorStack.h"
#include <memory>

namespace psdf
{

class EditorConstraint
{
  public:
    using SharedPtr = std::shared_ptr<EditorConstraint>;

    virtual bool evaluate(const EditorStack::SharedPtr &pStack, const EditorCommand::SharedPtr &pCommand) = 0;

  protected:
    EditorConstraint() = default;
};

} // namespace psdf
