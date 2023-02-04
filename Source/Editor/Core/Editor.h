#pragma once

#include "EditorAggregator.h"
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

    void addCommand(const EditorCommand::SharedPtr &pCommand);

    void addConsumer(EditorConsumer::SharedPtr pConsumer);
    void removeConsumer(const EditorConsumer::SharedPtr &pConsumer);

    void addConstraint(EditorConstraint::SharedPtr pConstraint);
    void removeConstraint(const EditorConstraint::SharedPtr &pConstraint);

    void transform(const EditorTransformation::SharedPtr &pTransformation);
    [[nodiscard]] EditorAggregationResult::SharedPtr reduce(const EditorAggregator::SharedPtr &pAggregation) const;

    [[nodiscard]] EditorStack::SharedPtr getEditorStack() const;

  protected:
    Editor(EditorStack::SharedPtr pStack);

  private:
    void addStackCommand(const StackCommand::SharedPtr &pStackCommand);
    void notifyConsumers(const EditorEvent::SharedPtr &pEvent);

  private:
    EditorStack::SharedPtr mpStack;
    std::vector<EditorConstraint::SharedPtr> mConstraints;
    std::vector<EditorConsumer::SharedPtr> mConsumers;
};

} // namespace psdf
