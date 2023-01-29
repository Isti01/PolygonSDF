#pragma once

#include "EditorAggregation.h"
#include "EditorConstraint.h"
#include "EditorConsumer.h"
#include "EditorStack.h"
#include "EditorTransformation.h"

#include <memory>
#include <vector>

namespace psdf
{

class Editor : public std::enable_shared_from_this<Editor>
{
  public:
    using SharedPtr = std::shared_ptr<Editor>;

    static SharedPtr create(EditorStack::SharedPtr pStack);

    void addCommand(EditorCommand::SharedPtr pCommand);

    void addConsumer(EditorConsumer::SharedPtr pConsumer);
    void removeConsumer(const EditorConsumer::SharedPtr &pConsumer);

    void addConstraint(EditorConstraint::SharedPtr pConstraint);
    void removeConstraint(const EditorConstraint::SharedPtr &pConstraint);

    void transform(EditorTransformation::SharedPtr &pTransformation);
    [[nodiscard]] EditorAggregationResult::SharedPtr reduce(const EditorAggregation::SharedPtr &pAggregation) const;

  private:
    void addStackCommand(const StackCommand::SharedPtr& pStackCommand);
    void notifyConsumers(const EditorEvent::SharedPtr &pEvent);

  protected:
    Editor(EditorStack::SharedPtr pStack);

  private:
    EditorStack::SharedPtr mpStack;
    std::vector<EditorConstraint::SharedPtr> mConstraints;
    std::vector<EditorConsumer::SharedPtr> mConsumers;
};

} // namespace psdf
