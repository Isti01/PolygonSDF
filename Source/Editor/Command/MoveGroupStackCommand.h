#pragma once

#include "StackCommand.h"
namespace psdf
{

class MoveGroupStackCommand : public StackCommand
{
  public:
    using SharedPtr = std::shared_ptr<MoveGroupStackCommand>;

    static SharedPtr create(size_t groupIndex, Point from, Point to);

    Polygon::SharedPtr perform(const Polygon::SharedPtr &pPolygon) const override;

    bool canMerge(const StackCommand::SharedPtr &pCommand) const override;
    StackCommand::SharedPtr merge(const StackCommand::SharedPtr &pOther) override;

    std::string getName() const override;

    size_t getGroupIndex() const;
    Point getFrom() const;
    Point getTo() const;

  protected:
    MoveGroupStackCommand(size_t groupIndex, Point from, Point to);

  private:
    size_t mGroupIndex;
    Point mFrom;
    Point mTo;
};

} // namespace psdf
