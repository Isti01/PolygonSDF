#pragma once

#include "../../Rendering/PolygonRenderer/PolygonRenderer.h"
#include "../Core/Editor.h"
#include "./Presenter/PolygonPresenter.h"
#include "./Presenter/SdfAlgorithmOutputPresenter.h"
#include "Input/InsertRemoveVertexInputHandler.h"
#include "Input/VertexMoveInputHandler.h"

#include <Falcor.h>
#include <memory>

namespace psdf
{
using namespace Falcor;

class VisualEditor
{
  public:
    using SharedPtr = std::shared_ptr<VisualEditor>;
    static SharedPtr create(Editor::SharedPtr pEditor);

    void render(RenderContext *pRenderContext, const Fbo::SharedPtr &pTargetFbo);

    bool onKeyEvent(const KeyboardEvent &keyEvent);
    bool onMouseEvent(const MouseEvent &mouseEvent);

  protected:
    VisualEditor(Editor::SharedPtr pEditor);

  private:
    void setActiveInputHandler(const MouseInputHandler::SharedPtr &pInputHandler);

  private:
    Editor::SharedPtr mpEditor = nullptr;
    PolygonRenderer::SharedPtr mpPolygonRenderer = nullptr;
    PolygonPresenter::SharedPtr mpPolygonPresenter = nullptr;
    SdfAlgorithmOutputPresenter::SharedPtr mpAlgorithmOutputPresenter = nullptr;
    VertexMoveInputHandler::SharedPtr mpVertexMover = nullptr;
    InsertRemoveVertexInputHandler::SharedPtr mpVertexInserter = nullptr;
    MouseInputHandler::SharedPtr mpActiveInputHandler = nullptr;
};

} // namespace psdf
