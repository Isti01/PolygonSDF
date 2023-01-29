#include "EditorStack.h"

using namespace psdf;

EditorStack::EditorStack(std::vector<StackEntry> stack) : mStack(std::move(stack))
{
}

EditorStack::SharedPtr EditorStack::create()
{
    return SharedPtr(new EditorStack());
}

EditorStack::SharedPtr EditorStack::create(std::vector<StackEntry> stack)
{
    return SharedPtr(new EditorStack(std::move(stack)));
}

Polygon::SharedPtr EditorStack::peekPolygon() const
{
    if (mStack.empty())
    {
        return nullptr;
    }
    return mStack.back().polygon;
}

void EditorStack::push(const StackCommand::SharedPtr &pCommand)
{
    auto topPolygon = peekPolygon();
    mStack.push_back(StackEntry{pCommand, pCommand->perform(topPolygon)});
}
