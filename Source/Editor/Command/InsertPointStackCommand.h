#pragma once

#include "StackCommand.h"

namespace psdf
{

class InsertPointStackCommand : public StackCommand
{
  public:
    using SharedPtr = std::shared_ptr<InsertPointStackCommand>;
    static SharedPtr create(size_t index, Point point);

    Polygon::SharedPtr perform(const Polygon::SharedPtr &polygon) const override;
    std::string getName() const override;
    size_t getIndex() const;
    Point getPoint() const;

  protected:
    InsertPointStackCommand(size_t index, Point point);

  private:
    size_t mIndex;
    Point mPoint;
};

} // namespace psdf
