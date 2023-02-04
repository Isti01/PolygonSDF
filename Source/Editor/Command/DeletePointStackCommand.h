#pragma once

#include "StackCommand.h"

namespace psdf
{

class DeletePointStackCommand : public StackCommand
{
  public:
    static StackCommand::SharedPtr create(size_t index);

    Polygon::SharedPtr perform(const Polygon::SharedPtr &polygon) const override;
    std::string getName() const override;

  protected:
    DeletePointStackCommand(size_t index);

  private:
    size_t mIndex;
};

} // namespace psdf
