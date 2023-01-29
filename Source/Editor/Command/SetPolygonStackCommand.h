#pragma once

#include "StackCommand.h"
namespace psdf
{

class SetPolygonStackCommand : public StackCommand
{
  public:
    static StackCommand::SharedPtr create(Polygon::SharedPtr pPolygon);

    [[nodiscard]] Polygon::SharedPtr perform(const Polygon::SharedPtr &polygon) const override;

    [[nodiscard]] std::string getName() const override;

    [[nodiscard]] Polygon::SharedPtr getPolygon() const;

  protected:
    SetPolygonStackCommand(Polygon::SharedPtr pPolygon);

  private:
    Polygon::SharedPtr mpPolygon;
};

} // namespace psdf
