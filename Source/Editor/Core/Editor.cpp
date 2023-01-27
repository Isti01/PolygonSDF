#include "Editor.h"
#include "../Event/ConstraintViolationEvent.h"
#include "../Event/NewCommandEvent.h"
#include "../Event/StackTransformedEvent.h"

using namespace psdf;

Editor::SharedPtr Editor::create()
{
    return SharedPtr(new Editor());
}

void Editor::addCommand(EditorCommand::SharedPtr &pCommand)
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

void Editor::addConsumer(EditorConsumer::SharedPtr &pConsumer)
{
    mConsumers.push_back(pConsumer);
}

void Editor::addConstraint(EditorConstraint::SharedPtr &pConstraint)
{
    mConstraints.push_back(pConstraint);
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
