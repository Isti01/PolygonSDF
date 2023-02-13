#pragma once

#include "../../Polygon/Polygon.h"
#include "../Core/EditorCommand.h"

namespace psdf
{

class StackCommand : public EditorCommand, public std::enable_shared_from_this<StackCommand>
{
  public:
    using SharedPtr = std::shared_ptr<StackCommand>;

    virtual Polygon::SharedPtr perform(const Polygon::SharedPtr &polygon) const = 0;
    virtual bool canMerge(const StackCommand::SharedPtr &pCommand) const;
    virtual StackCommand::SharedPtr merge(const StackCommand::SharedPtr &pOther);
};

} // namespace psdf
