#pragma once

#include "../../Polygon/Polygon.h"
#include "Falcor.h"

namespace psdf
{
using namespace Falcor;

class PolygonRenderer
{
  public:
    using SharedPtr = std::shared_ptr<PolygonRenderer>;
    void render(RenderContext *context);
    void setPolygon(const Polygon::SharedPtr &polygon);

  protected:
    virtual void init() = 0;
    virtual void uploadPolygonData() = 0;
    virtual void renderImpl(RenderContext *context) const = 0;

  private:
    void ensureInitialized();

  protected:
    Polygon::SharedPtr mpPolygon = nullptr;

  private:
    bool mInitialized = false;
};

} // namespace psdf
