#include "DeletePointEditorConstraint.h"
#include "../Command/DeletePointStackCommand.h"

using namespace psdf;

DeletePointEditorConstraint::SharedPtr DeletePointEditorConstraint::create()
{
    return SharedPtr(new DeletePointEditorConstraint());
}

std::string DeletePointEditorConstraint::getName() const
{
    return "DeletePointEditorConstraint";
}

bool DeletePointEditorConstraint::evaluate(const EditorStack::SharedPtr &pStack,
                                           const EditorCommand::SharedPtr &pCommand)
{
    if (std::dynamic_pointer_cast<DeletePointStackCommand>(pCommand))
    {
        auto topPolygon = pStack->peek();
        return topPolygon.has_value() && topPolygon->polygon->getPoints().size() > 3;
    }
    return true;
}
