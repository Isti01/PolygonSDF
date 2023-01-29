#pragma once

#include "../Command/StackCommand.h"
#include "EditorCommand.h"
#include "StackEntry.h"

#include <memory>
#include <vector>

namespace psdf
{

class EditorStack
{
  public:
    using SharedPtr = std::shared_ptr<EditorStack>;

    static SharedPtr create();
    static SharedPtr create(std::vector<StackEntry> stack);

    [[nodiscard]] Polygon::SharedPtr peekPolygon() const;

    void push(const StackCommand::SharedPtr& pCommand);

  protected:
    EditorStack() = default;
    EditorStack(std::vector<StackEntry> stack);

  private:
    std::vector<StackEntry> mStack;
};

} // namespace psdf
