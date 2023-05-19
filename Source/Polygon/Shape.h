#pragma once

#include "../Algorithm/SdfPlaneAlgorithmExecutionDesc.h"
#include "../Algorithm/SdfPlaneAlgorithmOutput.h"
#include "Edge.h"
#include "Outline.h"
#include "Vertex.h"
#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

class Shape : public std::enable_shared_from_this<Shape>
{
  public:
    using Vertices = Outline::Vertices;
    using Edges = Outline::Edges;

    using FloatVertices = Outline::FloatVertices;
    using FloatEdges = Outline::FloatEdges;

    using SharedPtr = std::shared_ptr<Shape>;
    static Shape::SharedPtr kStarterShape;
    static Shape::SharedPtr kSquareShape;

    static SharedPtr fromJson(const std::string &path);
    static SharedPtr create(std::vector<Outline> outlines);

    bool saveJson(const std::string &path) const;

    Vertex getCenter() const;
    double getCircumscribedCircleRadiusFromCenter() const;

    std::vector<Outline> getOutlines() const;
    Edges getAllEdges() const;

    FloatEdges getAllFloatEdges() const;

    SdfPlaneAlgorithmOutput::SharedPtr getAlgorithmOutput() const;
    void runAlgorithm(SdfPlaneAlgorithmExecutionDesc desc = kDefaultSdfPlaneAlgorithmExecutionDesc);

  private:
    Shape(std::vector<Outline> outlines);

  private:
    SdfPlaneAlgorithmOutput::SharedPtr mpSdfPlaneAlgorithmOutput = nullptr;
    std::vector<Outline> mOutlines;
};

} // namespace psdf
