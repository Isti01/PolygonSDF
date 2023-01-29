#include "Editor.h"
#include "../Event/ConstraintViolationEvent.h"
#include "../Event/NewStackCommandEvent.h"
#include "../Event/StackTransformedEvent.h"
#include "../Event/UnknownCommandEvent.h"
#include <algorithm>
#include <iterator>

using namespace psdf;

Editor::Editor(EditorStack::SharedPtr pStack) : mpStack(std::move(pStack))
{
}

Editor::SharedPtr Editor::create(EditorStack::SharedPtr pStack)
{
    return SharedPtr(new Editor(std::move(pStack)));
}

void Editor::addCommand(const EditorCommand::SharedPtr& pCommand)
{
    if (auto pStackCommand = std::dynamic_pointer_cast<StackCommand>(pCommand))
    {
        addStackCommand(pStackCommand);
        return;
    }

    this->notifyConsumers(UnknownCommandEvent::create(pCommand));
}

void Editor::addStackCommand(const StackCommand::SharedPtr &pStackCommand)
{
    for (auto &constraint : this->mConstraints)
    {
        if (!constraint->evaluate(this->mpStack, pStackCommand))
        {
            notifyConsumers(ConstraintViolationEvent::create(this->shared_from_this(), constraint, pStackCommand));
            return;
        }
    }

    mpStack->push(pStackCommand);
    notifyConsumers(NewStackCommandEvent::create(this->shared_from_this(), pStackCommand));
}

void Editor::addConsumer(EditorConsumer::SharedPtr pConsumer)
{
    mConsumers.emplace_back(std::move(pConsumer));
}

void Editor::removeConsumer(const EditorConsumer::SharedPtr &pConsumer)
{
    std::vector<EditorConsumer::SharedPtr> newVec;
    auto notIdentical = [&pConsumer](auto &element) { return element.get() != pConsumer.get(); };
    std::copy_if(mConsumers.begin(), mConsumers.end(), std::back_inserter(newVec), notIdentical);
    mConsumers = std::move(newVec);
}

void Editor::addConstraint(EditorConstraint::SharedPtr pConstraint)
{
    mConstraints.emplace_back(std::move(pConstraint));
}

void Editor::removeConstraint(const EditorConstraint::SharedPtr &pConstraint)
{
    std::vector<EditorConstraint::SharedPtr> newVec;
    auto notIdentical = [&pConstraint](auto &element) { return element.get() != pConstraint.get(); };
    std::copy_if(mConstraints.begin(), mConstraints.end(), std::back_inserter(newVec), notIdentical);
    mConstraints = std::move(newVec);
}

void Editor::transform(EditorTransformation::SharedPtr &pTransformation)
{
    pTransformation->transform(mpStack);
    notifyConsumers(StackTransformedEvent::create(this->shared_from_this(), pTransformation));
}

EditorAggregationResult::SharedPtr Editor::reduce(const EditorAggregator::SharedPtr &pAggregation) const
{
    return pAggregation->reduce(mpStack);
}

void Editor::notifyConsumers(const EditorEvent::SharedPtr &pEvent)
{
    for (auto &pConsumer : this->mConsumers)
    {
        pConsumer->accept(pEvent);
    }
}

EditorStack::SharedPtr Editor::getEditorStack() const
{
    return mpStack;
}
