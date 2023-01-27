#include "EditorStack.h"

using namespace psdf;

EditorStack::EditorStack(std::vector<EditorCommand::SharedPtr> stack) : mStack(std::move(stack))
{
}

EditorStack::SharedPtr EditorStack::create()
{
    return SharedPtr(new EditorStack());
}

EditorStack::SharedPtr EditorStack::create(std::vector<EditorCommand::SharedPtr> stack)
{
    return SharedPtr(new EditorStack(std::move(stack)));
}

void EditorStack::push(EditorCommand::SharedPtr pCommand)
{
    mStack.emplace_back(std::move(pCommand));
}
