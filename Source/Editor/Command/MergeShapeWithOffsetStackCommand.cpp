#include "MergeShapeWithOffsetStackCommand.h"

using namespace psdf;

MergeShapeWithOffsetStackCommand::SharedPtr MergeShapeWithOffsetStackCommand::create(Shape::SharedPtr pShape,
                                                                                     Vertex offset)
{
    return SharedPtr(new MergeShapeWithOffsetStackCommand(std::move(pShape), offset));
}

MergeShapeWithOffsetStackCommand::MergeShapeWithOffsetStackCommand(Shape::SharedPtr pShape, Vertex offset)
    : mpShape(std::move(pShape)), mOffset(offset)
{
}

Shape::SharedPtr MergeShapeWithOffsetStackCommand::perform(const Shape::SharedPtr &pShape) const
{
    std::vector<Outline> mergedOutlines = pShape ? pShape->getOutlines() : std::vector<Outline>();
    std::vector<Vertex> currentOutline;
    Vertex offset = mOffset;
    if (mpShape)
    {
        for (const auto &group : mpShape->getOutlines())
        {
            const auto &points = group.getVertices();
            std::transform(points.begin(), points.end(), std::back_inserter(currentOutline),
                           [&offset](const auto &point) { return point + offset; });
            mergedOutlines.emplace_back(currentOutline);
            currentOutline.clear();
        }
    }
    return Shape::create(mergedOutlines);
}

std::string MergeShapeWithOffsetStackCommand::getName() const
{
    return "MergeShapeWithOffsetStackCommand";
}
