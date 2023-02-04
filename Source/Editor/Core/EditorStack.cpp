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

size_t EditorStack::getSize() const
{
    return mStack.size();
}

void EditorStack::push(const StackCommand::SharedPtr &pCommand)
{
    auto topPolygon = peekPolygon();
    mStack.push_back(StackEntry{pCommand, pCommand->perform(topPolygon)});
}

void EditorStack::clear()
{
    mStack = std::vector<StackEntry>(); // std::vector<>::clear leaves the capacity unchanged
}

std::optional<StackEntry> EditorStack::pop()
{
    if (mStack.empty())
    {
        return std::nullopt;
    }

    StackEntry entry = mStack.back();
    mStack.pop_back();
    return {entry};
}
