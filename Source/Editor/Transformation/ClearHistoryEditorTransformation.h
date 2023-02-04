#pragma once

#include "../Core/EditorTransformation.h"
namespace psdf
{

class ClearHistoryEditorTransformation : public EditorTransformation
{
  public:
    static EditorTransformation::SharedPtr create();

    void transform(EditorStack::SharedPtr &pEditorStack) override;

  protected:
    ClearHistoryEditorTransformation() = default;
};

} // namespace psdf
