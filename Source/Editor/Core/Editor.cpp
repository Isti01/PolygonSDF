#include "Editor.h"
#include "../Event/ConstraintViolationEvent.h"
#include "../Event/NewCommandEvent.h"
#include "../Event/StackTransformedEvent.h"
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

void Editor::addCommand(EditorCommand::SharedPtr pCommand)
{
    for (auto &constraint : this->mConstraints)
    {
        if (!constraint->evaluate(this->mpStack, pCommand))
        {
            notifyConsumers(ConstraintViolationEvent::create(this->shared_from_this(), constraint, pCommand));
            return;
        }
    }

    mpStack->push(pCommand);
    notifyConsumers(NewCommandEvent::create(this->shared_from_this(), pCommand));
}

void Editor::addConsumer(EditorConsumer::SharedPtr pConsumer)
{
    mConsumers.emplace_back(std::move(pConsumer));
}

void Editor::removeConsumer(const EditorConsumer::SharedPtr &pConsumer)
{
    std::vector<EditorConsumer::SharedPtr> newVec;
    std::copy_if(mConsumers.begin(), mConsumers.end(), std::back_inserter(newVec),
                 [&pConsumer](auto &element) { return element.get() != pConsumer.get(); });
    mConsumers = std::move(newVec);
}

void Editor::addConstraint(EditorConstraint::SharedPtr pConstraint)
{
    mConstraints.emplace_back(std::move(pConstraint));
}

void Editor::removeConstraint(const EditorConstraint::SharedPtr &pConstraint)
{
    std::vector<EditorConstraint::SharedPtr> newVec;
    std::copy_if(mConstraints.begin(), mConstraints.end(), std::back_inserter(newVec),
                 [&pConstraint](auto &element) { return element.get() != pConstraint.get(); });
    mConstraints = std::move(newVec);
}

void Editor::transform(EditorTransformation::SharedPtr &pTransformation)
{
    pTransformation->transform(mpStack);
    notifyConsumers(StackTransformedEvent::create(this->shared_from_this(), pTransformation));
}
EditorAggregationResult::SharedPtr Editor::reduce(const EditorAggregation::SharedPtr &pAggregation) const
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
