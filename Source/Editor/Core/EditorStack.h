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

    void push(const EditorCommand::SharedPtr &pCommand)
    {
        mStack.push_back(pCommand);
    }

  private:
    std::vector<EditorCommand::SharedPtr> mStack;
};

} // namespace psdf
