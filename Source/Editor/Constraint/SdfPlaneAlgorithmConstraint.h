#pragma once

#include "../Core/EditorConstraint.h"

namespace psdf
{

class SdfPlaneAlgorithmConstraint : public EditorConstraint
{
  public:
    using SharedPtr = std::shared_ptr<SdfPlaneAlgorithmConstraint>;
    static SharedPtr create();

    bool evaluate(const EditorStack::SharedPtr &pStack, const EditorCommand::SharedPtr &pCommand) override;
    std::string getName() const override;

  protected:
    SdfPlaneAlgorithmConstraint() = default;
};

} // namespace psdf
