#include "DeleteOutlineEditorConstraint.h"
#include "../Command/DeleteOutlineStackCommand.h"

using namespace psdf;

DeleteOutlineEditorConstraint::SharedPtr DeleteOutlineEditorConstraint::create()
{
    return SharedPtr(new DeleteOutlineEditorConstraint());
}

bool DeleteOutlineEditorConstraint::evaluate(const EditorStack::SharedPtr &pStack,
                                           const EditorCommand::SharedPtr &pCommand)
{
    if (const auto &pDeleteCommand = std::dynamic_pointer_cast<DeleteOutlineStackCommand>(pCommand))
    {
        auto topPolygon = pStack->peek();
        return topPolygon.has_value() && topPolygon->pShape->getOutlines().size() > 1;
    }
    return true;
}

std::string DeleteOutlineEditorConstraint::getName() const
{
    return "DeleteOutlineEditorConstraint";
}
