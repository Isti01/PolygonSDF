#pragma once

#include <functional>

namespace psdf
{

class Benchmark
{
  public:
    Benchmark(const std::function<void()> &function);
    Benchmark(const std::string &file, const std::string &name, size_t executions,
              const std::function<void()> &function);

    void runAndSaveResults(const std::string &file, const std::string &name, size_t executions);

  private:
    std::vector<size_t> runAndGetResults(size_t executions);
    size_t executeAndGetTime();
    static size_t getTime();

  private:
    std::function<void()> mFunction;
};

} // namespace psdf
