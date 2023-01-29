#include "SetPolygonStackCommand.h"

using namespace psdf;

StackCommand::SharedPtr SetPolygonStackCommand::create(Polygon::SharedPtr pPolygon)
{
    return StackCommand::SharedPtr(new SetPolygonStackCommand(std::move(pPolygon)));
}

SetPolygonStackCommand::SetPolygonStackCommand(Polygon::SharedPtr pPolygon) : mpPolygon(std::move(pPolygon))
{
}

Polygon::SharedPtr SetPolygonStackCommand::perform(const Polygon::SharedPtr &polygon) const
{
    return mpPolygon;
}

std::string SetPolygonStackCommand::getName() const
{
    return "SetPolygonStackCommand";
}

Polygon::SharedPtr SetPolygonStackCommand::getPolygon() const
{
    return mpPolygon;
}
