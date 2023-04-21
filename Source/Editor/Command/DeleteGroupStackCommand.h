#pragma once

#include "StackCommand.h"

namespace psdf
{

class DeleteGroupStackCommand : public StackCommand
{
  public:
    using SharedPtr = std::shared_ptr<DeleteGroupStackCommand>;

    static SharedPtr create(size_t groupIndex);

    Polygon::SharedPtr perform(const Polygon::SharedPtr &polygon) const override;
    std::string getName() const override;

  protected:
    DeleteGroupStackCommand(size_t groupIndex);

  private:
    size_t mGroupIndex;
};

} // namespace psdf
