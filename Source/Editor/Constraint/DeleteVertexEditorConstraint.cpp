#include "DeleteVertexEditorConstraint.h"
#include "../Command/DeleteVertexStackCommand.h"

using namespace psdf;

DeleteVertexEditorConstraint::SharedPtr DeleteVertexEditorConstraint::create()
{
    return SharedPtr(new DeleteVertexEditorConstraint());
}

std::string DeleteVertexEditorConstraint::getName() const
{
    return "DeleteVertexEditorConstraint";
}

bool DeleteVertexEditorConstraint::evaluate(const EditorStack::SharedPtr &pStack,
                                            const EditorCommand::SharedPtr &pCommand)
{
    if (const auto &pDeleteCommand = std::dynamic_pointer_cast<DeleteVertexStackCommand>(pCommand))
    {
        auto topPolygon = pStack->peek();
        return topPolygon.has_value() &&
               topPolygon->pShape->getOutlines()[pDeleteCommand->getOutlineIndex()].getVertices().size() > 3;
    }
    return true;
}
