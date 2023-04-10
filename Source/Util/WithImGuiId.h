#pragma once

namespace psdf
{

class WithImGuiId
{
  public:
    WithImGuiId(int id);
    WithImGuiId(const char *id);

    ~WithImGuiId();
};

} // namespace psdf
