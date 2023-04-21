#pragma once

#include "../Core/EditorConstraint.h"

namespace psdf
{

class DeleteGroupEditorConstraint : public EditorConstraint
{
  public:
    using SharedPtr = std::shared_ptr<DeleteGroupEditorConstraint>;
    static SharedPtr create();

    std::string getName() const override;
    bool evaluate(const psdf::EditorStack::SharedPtr &pStack, const psdf::EditorCommand::SharedPtr &pCommand) override;

  protected:
    DeleteGroupEditorConstraint() = default;
};

} // namespace psdf
