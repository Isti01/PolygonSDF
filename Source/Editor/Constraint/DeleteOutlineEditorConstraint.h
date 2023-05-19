#pragma once

#include "../Core/EditorConstraint.h"

namespace psdf
{

class DeleteOutlineEditorConstraint : public EditorConstraint
{
  public:
    using SharedPtr = std::shared_ptr<DeleteOutlineEditorConstraint>;
    static SharedPtr create();

    std::string getName() const override;
    bool evaluate(const psdf::EditorStack::SharedPtr &pStack, const psdf::EditorCommand::SharedPtr &pCommand) override;

  protected:
    DeleteOutlineEditorConstraint() = default;
};

} // namespace psdf
