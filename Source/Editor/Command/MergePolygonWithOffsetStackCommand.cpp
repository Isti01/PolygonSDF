#include "MergePolygonWithOffsetStackCommand.h"

using namespace psdf;

MergePolygonWithOffsetStackCommand::SharedPtr MergePolygonWithOffsetStackCommand::create(Polygon::SharedPtr pPolygon,
                                                                                         Point offset)
{
    return SharedPtr(new MergePolygonWithOffsetStackCommand(std::move(pPolygon), offset));
}

MergePolygonWithOffsetStackCommand::MergePolygonWithOffsetStackCommand(Polygon::SharedPtr pPolygon, Point offset)
    : mpPolygon(std::move(pPolygon)), mOffset(offset)
{
}

Polygon::SharedPtr MergePolygonWithOffsetStackCommand::perform(const Polygon::SharedPtr &polygon) const
{
    std::vector<SubPolygon> mergedPolygons = polygon ? polygon->getPolygons() : std::vector<SubPolygon>();
    std::vector<Point> currentGroup;
    Point offset = mOffset;
    if (mpPolygon)
    {
        for (const auto &group : mpPolygon->getPolygons())
        {
            const auto &points = group.getPoints();
            std::transform(points.begin(), points.end(), std::back_inserter(currentGroup),
                           [&offset](const auto &point) { return point + offset; });
            mergedPolygons.emplace_back(currentGroup);
            currentGroup.clear();
        }
    }
    return Polygon::create(mergedPolygons);
}

std::string MergePolygonWithOffsetStackCommand::getName() const
{
    return "MergePolygonWithOffsetStackCommand";
}
