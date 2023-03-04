#pragma once

#include "../Core/Editor.h"
#include "../Core/EditorEvent.h"

namespace psdf
{

class StackTransformedEvent : public EditorEvent
{
  public:
    static SharedPtr create(const Editor::SharedPtr &pEditor, const EditorTransformation::SharedPtr &pTransformation);

    std::string getName() const override;
    [[nodiscard]] EditorTransformation::SharedPtr getTransformation() const;

  protected:
    StackTransformedEvent(Editor::SharedPtr pEditor, EditorTransformation::SharedPtr pTransformation);

  private:
    Editor::SharedPtr mpEditor;
    EditorTransformation::SharedPtr mpTransformation;
};

} // namespace psdf
