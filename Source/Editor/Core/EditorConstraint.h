#pragma once

#include "EditorStack.h"
#include <memory>

namespace psdf
{

class EditorConstraint
{
  public:
    using SharedPtr = std::shared_ptr<EditorConstraint>;

    virtual std::string getName() const = 0;
    virtual bool evaluate(const EditorStack::SharedPtr &pStack, const EditorCommand::SharedPtr &pCommand) = 0;

    virtual ~EditorConstraint() = default;
};

} // namespace psdf
