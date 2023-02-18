#pragma once

#include <memory>
namespace psdf
{

class Deferred : public std::shared_ptr<void>
{
  public:
    template <typename F>
    Deferred(F &&args) : std::shared_ptr<void>(nullptr, std::forward<F>(args))
    {
    }
};

} // namespace psdf
