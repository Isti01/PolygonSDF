#pragma once

#include "../Core/EditorConstraint.h"

namespace psdf
{

class DeleteVertexEditorConstraint : public EditorConstraint
{
  public:
    using SharedPtr = std::shared_ptr<DeleteVertexEditorConstraint>;

    static SharedPtr create();

    std::string getName() const override;
    bool evaluate(const EditorStack::SharedPtr &pStack, const EditorCommand::SharedPtr &pCommand) override;

    ~DeleteVertexEditorConstraint() override = default;

  protected:
    DeleteVertexEditorConstraint() = default;
};

} // namespace psdf
