#include "Benchmark.h"

#include <chrono>
#include <fstream>
#include <json/json.hpp>

using json = nlohmann::json;
using namespace psdf;

Benchmark::Benchmark(const std::function<void()> &function) : mFunction(function)
{
}

Benchmark::Benchmark(const std::string &file, const std::string &name, size_t executions,
                     const std::function<void()> &function)
    : mFunction(function)
{
    runAndSaveResults(file, name, executions);
}

void Benchmark::runAndSaveResults(const std::string &file, const std::string &name, size_t executions)
{
    std::vector<json> measurements;
    for (auto result : runAndGetResults(executions))
    {
        json value = result;
        measurements.emplace_back(std::move(value));
    }
    json output;
    output["name"] = name;
    output["measurements"] = measurements;
    std::ofstream(file) << output.dump();
}

std::vector<size_t> Benchmark::runAndGetResults(size_t executions)
{
    std::vector<size_t> timings;
    timings.reserve(executions);
    for (size_t i = 0; i < executions; i++)
    {
        timings.emplace_back(executeAndGetTime());
    }
    return timings;
}

size_t Benchmark::executeAndGetTime()
{
    size_t start = getTime();
    mFunction();
    return getTime() - start;
}
size_t Benchmark::getTime()
{
    auto time = std::chrono::system_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(time).count();
}
