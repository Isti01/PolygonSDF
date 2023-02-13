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

std::optional<StackEntry> EditorStack::peek() const
{
    if (mStack.empty())
    {
        return std::nullopt;
    }
    return mStack.back();
}

size_t EditorStack::getSize() const
{
    return mStack.size();
}

void EditorStack::push(const StackCommand::SharedPtr &pCommand)
{
    auto topPolygon = peek().value_or(StackEntry::kEmptyStackEntry).polygon;
    mStack.push_back(StackEntry{pCommand, pCommand->perform(topPolygon)});
}

void EditorStack::pushReplacement(const StackCommand::SharedPtr &pCommand)
{
    auto topPolygon = pop().value_or(StackEntry::kEmptyStackEntry).polygon;
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
