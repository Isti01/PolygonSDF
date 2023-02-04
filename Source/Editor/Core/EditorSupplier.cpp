#include "EditorSupplier.h"

using namespace psdf;

EditorSupplier::SharedPtr EditorSupplier::create(Editor::SharedPtr pEditor)
{
    return SharedPtr(new EditorSupplier(std::move(pEditor)));
}

EditorSupplier::EditorSupplier(Editor::SharedPtr pEditor) : mpEditor(std::move(pEditor))
{
}

void EditorSupplier::dispatchCommand(const EditorCommand::SharedPtr &pCommand)
{
    mpEditor->addCommand(pCommand);
}
