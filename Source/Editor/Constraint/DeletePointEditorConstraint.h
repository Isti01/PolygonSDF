#pragma once

#include "../Core/EditorConstraint.h"

namespace psdf
{

class DeletePointEditorConstraint : public EditorConstraint
{
  public:
    using SharedPtr = std::shared_ptr<DeletePointEditorConstraint>;

    static SharedPtr create();

    std::string getName() const override;
    bool evaluate(const EditorStack::SharedPtr &pStack, const EditorCommand::SharedPtr &pCommand) override;

    ~DeletePointEditorConstraint() override = default;

  protected:
    DeletePointEditorConstraint() = default;
};

} // namespace psdf
