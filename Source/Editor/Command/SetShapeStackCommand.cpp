#include "SetShapeStackCommand.h"

using namespace psdf;

StackCommand::SharedPtr SetShapeStackCommand::create(Shape::SharedPtr pShape)
{
    return StackCommand::SharedPtr(new SetShapeStackCommand(std::move(pShape)));
}

SetShapeStackCommand::SetShapeStackCommand(Shape::SharedPtr pShape) : mpShape(std::move(pShape))
{
}

Shape::SharedPtr SetShapeStackCommand::perform(const Shape::SharedPtr &pShape) const
{
    return mpShape;
}

std::string SetShapeStackCommand::getName() const
{
    return "SetShapeStackCommand";
}

Shape::SharedPtr SetShapeStackCommand::getShape() const
{
    return mpShape;
}
