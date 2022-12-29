#pragma once

#include "Falcor.h"
#include "RenderObject.h"

namespace psdf
{
using namespace Falcor;

class FullScreenTriangle
{
  public:
    using SharedPtr = std::shared_ptr<FullScreenTriangle>;

    static SharedPtr create(GraphicsState::SharedPtr pGraphicsState);
    FullScreenTriangle(GraphicsState::SharedPtr pGraphicsState);

    void init();
    void setFbo(const Fbo::SharedPtr &pFbo);
    void render(RenderContext *pRenderContext);

    GraphicsVars::SharedPtr getGraphicsVars();

  private:
    GraphicsVars::SharedPtr mpProgramVars = nullptr;
    GraphicsState::SharedPtr mpGraphicsState = nullptr;
    RenderObject::SharedPtr mpTriangle = nullptr;
};

} // namespace psdf
