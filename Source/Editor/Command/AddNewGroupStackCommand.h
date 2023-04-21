#pragma once

#include "StackCommand.h"

namespace psdf
{
using namespace psdf;

class AddNewGroupStackCommand : public StackCommand
{
  public:
    using SharedPtr = std::shared_ptr<AddNewGroupStackCommand>;
    static SharedPtr create(SubPolygon newGroup);

    Polygon::SharedPtr perform(const Polygon::SharedPtr &polygon) const override;
    std::string getName() const override;

  protected:
    AddNewGroupStackCommand(SubPolygon newGroup);

  private:
    SubPolygon mNewGroup;
};

} // namespace psdf
