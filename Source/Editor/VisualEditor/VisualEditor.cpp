#include "VisualEditor.h"
#include "../../Rendering/PolygonRenderer/PolygonRendererFactory.h"
#include "Input/VertexMoveInputHandler.h"

using namespace psdf;

VisualEditor::SharedPtr VisualEditor::create(Editor::SharedPtr pEditor)
{
    return SharedPtr(new VisualEditor(std::move(pEditor)));
}

VisualEditor::VisualEditor(Editor::SharedPtr pEditor)
    : mpEditor(std::move(pEditor)),
      mpPolygonPresenter(PolygonPresenter::create(mpEditor, PolygonRendererFactory::getPolygonRenderer())),
      mpVertexMover(VertexMoveInputHandler::create(mpEditor)), mpActiveInputHandler(mpPolygonPresenter)
{
}

void VisualEditor::render(RenderContext *pRenderContext, const Fbo::SharedPtr &pTargetFbo)
{
    mpPolygonPresenter->render(pRenderContext, pTargetFbo);
}

bool VisualEditor::onKeyEvent(const KeyboardEvent &keyEvent)
{
    if ((bool)keyEvent.mods) // we don't use modifiers
    {
        return false;
    }

    if (keyEvent.key == Input::Key::M)
    {
        setActiveInputHandler(mpVertexMover);
    }
    else if (keyEvent.key == Input::Key::V)
    {
        setActiveInputHandler(mpPolygonPresenter);
    }

    return false;
}

bool VisualEditor::onMouseEvent(const MouseEvent &mouseEvent)
{
    if (mpActiveInputHandler)
    {
        return mpActiveInputHandler->onMouseEvent(mouseEvent);
    }
    return false;
}

void VisualEditor::setActiveInputHandler(const MouseInputHandler::SharedPtr &pInputHandler)
{
    if (mpActiveInputHandler != pInputHandler)
    {
        mpActiveInputHandler = pInputHandler;
        mpActiveInputHandler->resetInputState();
    }
}
