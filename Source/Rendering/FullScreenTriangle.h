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

    FullScreenTriangle(Program::Desc programDesc);

    static SharedPtr create(Program::Desc programDesc);

    void init();
    void setFbo(const Fbo::SharedPtr &pFbo);
    void render(RenderContext *pRenderContext);

  private:
    Program::Desc mProgramDesc;

    GraphicsVars::SharedPtr mpProgramVars = nullptr;
    GraphicsState::SharedPtr mpGraphicsState = nullptr;
    RenderObject::SharedPtr mpTriangle = nullptr;
};

} // namespace psdf
