#pragma once

#include "../../../Rendering/PolygonRenderer/PolygonRenderer.h"
#include "../../Core/Editor.h"
#include "../Input/MouseInputHandler.h"

#include <Falcor.h>

namespace psdf
{

class Presenter : public MouseInputHandler
{
  public:
    using SharedPtr = std::shared_ptr<Presenter>;

    virtual void render(RenderContext *pRenderContext, const Fbo::SharedPtr &pTargetFbo) = 0;
};

} // namespace psdf
