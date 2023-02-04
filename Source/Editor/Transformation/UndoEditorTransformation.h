#pragma once

#include "../Core/EditorTransformation.h"

namespace psdf
{

class UndoEditorTransformation : public EditorTransformation
{
  public:
    static EditorTransformation::SharedPtr create();
    void transform(EditorStack::SharedPtr &pEditorStack) override;

  protected:
    UndoEditorTransformation() = default;
};

} // namespace psdf
