#pragma once

#include "EditorCommand.h"

#include <memory>
#include <vector>

namespace psdf
{

class EditorStack
{
  public:
    using SharedPtr = std::shared_ptr<EditorStack>;

    static SharedPtr create();
    static SharedPtr create(std::vector<EditorCommand::SharedPtr> stack);

    void push(EditorCommand::SharedPtr pCommand);

  protected:
    EditorStack() = default;
    EditorStack(std::vector<EditorCommand::SharedPtr> stack);

  private:
    std::vector<EditorCommand::SharedPtr> mStack;
};

} // namespace psdf
