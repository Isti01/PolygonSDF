#pragma once

#include "EditorStack.h"

#include <memory>

namespace psdf
{

class EditorTransformation
{
  public:
    using SharedPtr = std::shared_ptr<EditorTransformation>;

    virtual void transform(EditorStack::SharedPtr &pEditorStack) = 0;
};

} // namespace psdf
