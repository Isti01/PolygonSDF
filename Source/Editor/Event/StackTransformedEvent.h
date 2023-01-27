#pragma once

#include "../Core/Editor.h"
#include "../Core/EditorEvent.h"

namespace psdf
{

class StackTransformedEvent : public EditorEvent
{
  public:
    static SharedPtr create(const Editor::SharedPtr &pEditor, const EditorTransformation::SharedPtr &pTransformation);

    StackTransformedEvent(Editor::SharedPtr pEditor, EditorTransformation::SharedPtr pTransformation);

    [[nodiscard]] EditorTransformation::SharedPtr getTransformation() const;

  private:
    Editor::SharedPtr mpEditor;
    EditorTransformation::SharedPtr mpTransformation;
};

} // namespace psdf
