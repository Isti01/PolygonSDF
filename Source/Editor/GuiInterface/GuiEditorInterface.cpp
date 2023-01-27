#include "GuiEditorInterface.h"

using namespace psdf;

GuiEditorInterface::SharedPtr GuiEditorInterface::create(Editor::SharedPtr pEditor)
{
    return SharedPtr(new GuiEditorInterface(std::move(pEditor)));
}

GuiEditorInterface::GuiEditorInterface(Editor::SharedPtr pEditor)
    : mpEditor(std::move(pEditor)), mpCommandSupplier(EditorSupplier::create(mpEditor)),
      mpEventConsumer(GuiEditorEventConsumer::create())
{
    mpEditor->addConsumer(std::static_pointer_cast<EditorConsumer>(mpEventConsumer));
}

GuiEditorInterface::~GuiEditorInterface()
{
    mpEditor->removeConsumer(std::static_pointer_cast<EditorConsumer>(mpEventConsumer));
}
