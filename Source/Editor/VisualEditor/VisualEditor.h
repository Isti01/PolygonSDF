#pragma once

#include "../../Rendering/PolygonRenderer/PolygonRenderer.h"
#include "../Consumer/PropertyUpdatingEditorConsumer.h"
#include "../Core/Editor.h"
#include "./Presenter/PolygonPresenter.h"
#include "./Presenter/SdfAlgorithmOutputPresenter.h"
#include "Input/InsertRemoveVertexInputHandler.h"
#include "Input/MoveInputHandler.h"

#include <Falcor.h>

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

    ~VisualEditor();

  protected:
    VisualEditor(Editor::SharedPtr pEditor);

  private:
    void showGui();
    void hideGui();
    void setActiveInputHandler(const MouseInputHandler::SharedPtr &pInputHandler);

  private:
    Editor::SharedPtr mpEditor = nullptr;
    PolygonRenderer::SharedPtr mpEditorPolygonRenderer = nullptr;
    PolygonRenderer::SharedPtr mpAlgorithmPolygonRenderer = nullptr;
    PropertyUpdatingEditorConsumer::SharedPtr mpEditorRendererUpdatingConsumer = nullptr;
    PropertyUpdatingEditorConsumer::SharedPtr mpAlgorithmRendererUpdatingConsumer = nullptr;
    PolygonPresenter::SharedPtr mpPolygonPresenter = nullptr;
    SdfAlgorithmOutputPresenter::SharedPtr mpAlgorithmOutputPresenter = nullptr;
    MoveInputHandler::SharedPtr mpVertexMover = nullptr;
    MoveInputHandler::SharedPtr mpGroupMover = nullptr;
    InsertRemoveVertexInputHandler::SharedPtr mpVertexInserter = nullptr;
    MouseInputHandler::SharedPtr mpActiveInputHandler = nullptr;
    StackPeekingEditorAggregator::SharedPtr mpStackPeekingAggregator = nullptr;
};

} // namespace psdf
