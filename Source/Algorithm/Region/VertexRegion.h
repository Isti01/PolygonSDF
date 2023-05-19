#pragma once

#include "../../Polygon/Vertex.h"
#include "EdgeRegion.h"
#include "Region.h"
#include "VertexRegionBoundVertex.h"

namespace psdf
{

class VertexRegion : public Region
{
  public:
    VertexRegion(Vertex vertex, double cornerSign, size_t subdivisions, double initialBoundScale);
    VertexRegion(std::vector<glm::dvec2> bounds, Vertex vertex, double cornerSign, size_t subdivisions);

    static void cutWithVertices(std::vector<VertexRegion> &vertexRegions, const std::vector<VertexRegion> &cuttingRegions);
    static void cutWithEdges(std::vector<VertexRegion> &vertexRegions, const std::vector<EdgeRegion> &edgeRegions);

    void createMesh(std::vector<VertexRegionBoundVertex> &vertices, std::vector<uint32_t> &indices,
                    Vertex fanCenter) const;

    Vertex getVertex() const;
    double getCornerSign() const;
    double getDistanceToPointInsideBounds(Vertex vertex) const override;

  private:
    Vertex mVertex;
    double mCornerSign;
    size_t mSubdivisions;
};

} // namespace psdf
