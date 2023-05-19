#pragma once

#include "StackCommand.h"

namespace psdf
{

class MoveOutlineStackCommand : public StackCommand
{
  public:
    using SharedPtr = std::shared_ptr<MoveOutlineStackCommand>;

    static SharedPtr create(size_t outlineIndex, Vertex from, Vertex to);

    Shape::SharedPtr perform(const Shape::SharedPtr &pShape) const override;

    bool canMerge(const StackCommand::SharedPtr &pCommand) const override;
    StackCommand::SharedPtr merge(const StackCommand::SharedPtr &pOther) override;

    std::string getName() const override;

    size_t getOutlineIndex() const;
    Vertex getFrom() const;
    Vertex getTo() const;

  protected:
    MoveOutlineStackCommand(size_t outlineIndex, Vertex from, Vertex to);

  private:
    size_t mOutlineIndex;
    Vertex mFrom;
    Vertex mTo;
};

} // namespace psdf
