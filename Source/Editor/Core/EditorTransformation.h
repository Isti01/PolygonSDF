#pragma once

#include "EditorStack.h"

#include <memory>

namespace psdf
{

class EditorTransformation
{
  public:
    using SharedPtr = std::shared_ptr<EditorTransformation>;

    virtual std::string getName() const = 0;
    virtual void transform(EditorStack::SharedPtr &pEditorStack) = 0;

    virtual ~EditorTransformation() = default;
};

} // namespace psdf
