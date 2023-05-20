#pragma once

#include "../../Shape/Edge.h"
#include "Region.h"

namespace psdf
{
class VertexRegion;
class EdgeRegion : public Region
{
  public:
    EdgeRegion(const Edge &edge, double initialBoundScale);
    EdgeRegion(std::vector<glm::dvec2> bounds, Edge edge);

    Edge getEdge() const;
    glm::dvec2 getDir() const;
    double getDistanceToPointInsideBounds(Vertex point) const override;

    static void cutWithVertices(std::vector<EdgeRegion> &edgeRegions, const std::vector<VertexRegion> &vertexRegions);
    static void cutWithEdges(std::vector<EdgeRegion> &edgeRegions, const std::vector<EdgeRegion> &cuttingRegions);

    void createMesh(std::vector<EdgeRegionBoundVertex> &vertices, std::vector<uint32_t> &indices,
                    Vertex fanCenter) const;

  private:
    static glm::dvec2 computeParabolics(const glm::dvec2 &point, const glm::dvec2 &normal, const glm::dvec2 &bPoint);
    static glm::dvec2 computeBisectorIntersection(const glm::dvec2 &point, const glm::dvec2 &normal,
                                                  const glm::dvec2 &bPoint, const glm::dvec2 &bNormal,
                                                  const glm::dvec2 &g, bool isParallel);

  private:
    Edge mEdge;
};

} // namespace psdf
