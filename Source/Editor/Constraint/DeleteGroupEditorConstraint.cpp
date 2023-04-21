#include "DeleteGroupEditorConstraint.h"
#include "../Command/DeleteGroupStackCommand.h"

using namespace psdf;

DeleteGroupEditorConstraint::SharedPtr DeleteGroupEditorConstraint::create()
{
    return SharedPtr(new DeleteGroupEditorConstraint());
}

bool DeleteGroupEditorConstraint::evaluate(const EditorStack::SharedPtr &pStack,
                                           const EditorCommand::SharedPtr &pCommand)
{
    if (const auto &pDeleteCommand = std::dynamic_pointer_cast<DeleteGroupStackCommand>(pCommand))
    {
        auto topPolygon = pStack->peek();
        return topPolygon.has_value() && topPolygon->polygon->getPolygons().size() > 3;
    }
    return true;
}

std::string DeleteGroupEditorConstraint::getName() const
{
    return "DeleteGroupEditorConstraint";
}
