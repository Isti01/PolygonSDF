#include "../Source/Shape/Shape.h"
#include "Benchmark.h"

using namespace psdf;

void benchmarkPolygonAlgorithm(const std::string &name, const Shape::SharedPtr &pShape,
                               const std::vector<size_t> &subdivisions, size_t executions)
{
    auto desc = kDefaultSdfPlaneAlgorithmExecutionDesc;
    Benchmark benchmark{[&desc, pShape]() { pShape->runAlgorithm(desc); }};
    for (auto subdivision : subdivisions)
    {
        desc.vertexRegionSubdivision = subdivision;
        std::string benchmarkName = name + std::to_string(subdivision);
        std::cout << "Running benchmark: " << benchmarkName << std::endl;
        benchmark.runAndSaveResults("Benchmarks/" + benchmarkName + ".json", benchmarkName, executions);
    }
}

int main()
{
    std::filesystem::create_directories("Benchmarks");
    const std::vector<size_t> subdivisionsToBenchmark{3, 10, 25, 50, 100};
    const size_t executions = 100;

    benchmarkPolygonAlgorithm("low_vertex_count_", Shape::fromJson("Data/BenchmarkData/cat.json"),
                              subdivisionsToBenchmark, executions);
    benchmarkPolygonAlgorithm("text_", Shape::fromJson("Data/BenchmarkData/GREAT_WORK.json"), subdivisionsToBenchmark,
                              executions);
    benchmarkPolygonAlgorithm("high_vertex_count_", Shape::fromJson("Data/BenchmarkData/zoo.json"),
                              subdivisionsToBenchmark, executions);
}
