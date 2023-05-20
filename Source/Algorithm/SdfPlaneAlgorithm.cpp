#include "SdfPlaneAlgorithm.h"

using namespace psdf;

static bool isCcwWindingOrder(const Outline &outline)
{
    double sum = 0;
    const Outline::Vertices &vertices = outline.getVertices();
    size_t verticesSize = vertices.size();
    for (size_t i = 0; i < verticesSize; i++)
    {
        Vertex vertex1 = vertices[i];
        Vertex vertex2 = vertices[(i + 1) % verticesSize];
        sum += (vertex2.x - vertex1.x) * (vertex2.y + vertex1.y);
    }

    return sum < 0;
}

static bool isOutlineInside(size_t polygonIndex, const std::vector<Outline> &polygons)
{
    bool isInside = false;

    // checking only one of the vertices is enough, because we don't work with self-intersecting shapes
    glm::dvec2 coordToCheck = polygons[polygonIndex].getVertices()[0];

    for (size_t j = 0; j < polygons.size(); j++)
    {
        if (j == polygonIndex)
        {
            continue;
        }

        for (const auto &edge : polygons[j].getEdges())
        {
            glm::dvec2 e = edge.getVertex1() - edge.getVertex2();
            glm::dvec2 w = coordToCheck - edge.getVertex2();
            glm::bvec3 winding{
                coordToCheck.y >= edge.getVertex2().y,
                coordToCheck.y<edge.getVertex1().y, e.x * w.y> e.y * w.x,
            };
            if (all(winding) || all(glm::not_(winding)))
            {
                isInside = !isInside;
            }
        }
    }
    return isInside;
}

static void reorderVerticesForTheAlgorithm(std::vector<Outline> &reorderedPolygons)
{
    for (size_t i = 0; i < reorderedPolygons.size(); i++)
    {
        auto &outline = reorderedPolygons[i];
        bool isPolygonCcWindingOrder = isCcwWindingOrder(outline);
        bool isOnInside = isOutlineInside(i, reorderedPolygons);
        if (isOnInside && isPolygonCcWindingOrder || (!isOnInside && !isPolygonCcWindingOrder))
        {
            Outline::Vertices verticesCopy = outline.getVertices();
            std::reverse(verticesCopy.begin(), verticesCopy.end());
            outline = Outline(std::move(verticesCopy));
        }
    }
}

SdfPlaneAlgorithmOutput::SharedPtr SdfPlaneAlgorithm::calculateForShape(const Shape::SharedPtr &pShape,
                                                                        SdfPlaneAlgorithmExecutionDesc desc)
{
    std::vector<EdgeRegion> edgeRegions;
    std::vector<VertexRegion> vertexRegions;

    std::vector<Outline> reorderedPolygons = pShape->getOutlines();
    if (desc.reorderPoints)
    {
        reorderVerticesForTheAlgorithm(reorderedPolygons);
    }
    for (const auto &outline : reorderedPolygons)
    {
        const std::vector<Edge> &edges = outline.getEdges();

        size_t size = edges.size();
        for (int i = 0; i < size; i++)
        {
            Edge edge1 = edges[i];
            Edge edge2 = edges[(i + 1) % size];

            glm::dvec2 edgeVector1 = edge1.getEdgeVector();
            glm::dvec2 edgeVector2 = edge2.getEdgeVector();
            double cornerSign = glm::sign(glm::dot(glm::dvec2{-edgeVector1.y, edgeVector1.x}, edgeVector2));

            edgeRegions.emplace_back(edge1, desc.initialBoundScale);
            edgeRegions.back().polyCut({edge1.getVertex2(), edge1.getVertex1()}, {edgeVector1, -edgeVector1});
            vertexRegions.emplace_back(edge1.getVertex2(), cornerSign, desc.vertexRegionSubdivision,
                                       desc.initialBoundScale);
            vertexRegions.back().polyCut({edge1.getVertex2(), edge1.getVertex2()}, {edgeVector2, -edgeVector1});
        }
    }

    VertexRegion::cutWithVertices(vertexRegions, vertexRegions);
    VertexRegion::cutWithEdges(vertexRegions, edgeRegions);

    EdgeRegion::cutWithVertices(edgeRegions, vertexRegions);
    EdgeRegion::cutWithEdges(edgeRegions, edgeRegions);

    return SdfPlaneAlgorithmOutput::create(vertexRegions, edgeRegions);
}
