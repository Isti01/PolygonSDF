#include "VisualEditor.h"
#include "../../Rendering/PolygonRenderer/PolygonRendererFactory.h"
#include "../PublishedEvent/HideGuiPublishedEvent.h"
#include "../PublishedEvent/ShowGuiPublishedEvent.h"
#include "Input/VertexMoveInputHandler.h"

using namespace psdf;

VisualEditor::SharedPtr VisualEditor::create(Editor::SharedPtr pEditor)
{
    return SharedPtr(new VisualEditor(std::move(pEditor)));
}

VisualEditor::VisualEditor(Editor::SharedPtr pEditor)
    : mpEditor(std::move(pEditor)), mpPolygonRenderer(PolygonRendererFactory::getPolygonRenderer()),
      mpPolygonPresenter(PolygonPresenter::create(mpEditor, mpPolygonRenderer)),
      mpVertexMover(VertexMoveInputHandler::create(mpEditor, mpPolygonRenderer)),
      mpVertexInserter(InsertRemoveVertexInputHandler::create(mpEditor, mpPolygonRenderer)),
      mpActiveInputHandler(mpPolygonPresenter), mpStackPeekingAggregator(StackPeekingEditorAggregator::create()),
      mpAlgorithmOutputPresenter(
          SdfAlgorithmOutputPresenter::create(mpEditor, PolygonRendererFactory::getAlgorithmOutputRenderer()))
{
}

void VisualEditor::render(RenderContext *pRenderContext, const Fbo::SharedPtr &pTargetFbo)
{
    if (mpActiveInputHandler == mpAlgorithmOutputPresenter)
    {
        mpAlgorithmOutputPresenter->render(pRenderContext, pTargetFbo);
    }
    else
    {
        mpPolygonPresenter->render(pRenderContext, pTargetFbo);
    }
}

bool VisualEditor::onKeyEvent(const KeyboardEvent &keyEvent)
{
    if ((bool)keyEvent.mods) // we don't use modifiers
    {
        return false;
    }
    if (keyEvent.type != Falcor::KeyboardEvent::Type::KeyPressed) // we don't handle other scenarios
    {
        return false;
    }

    if (keyEvent.key == Input::Key::M)
    {
        showGui();
        setActiveInputHandler(mpVertexMover);
        return true;
    }

    if (keyEvent.key == Input::Key::V)
    {
        showGui();
        setActiveInputHandler(mpPolygonPresenter);
        return true;
    }

    if (keyEvent.key == Input::Key::I)
    {
        showGui();
        setActiveInputHandler(mpVertexInserter);
        return true;
    }

    if (keyEvent.key == Input::Key::D)
    {
        auto pPolygon = mpStackPeekingAggregator->peekEditor(mpEditor)->getEntry().polygon;
        if (pPolygon && pPolygon->getAlgorithmOutput())
        {
            hideGui();
            setActiveInputHandler(mpAlgorithmOutputPresenter);
        }
        else
        {
            msgBox("There is nothing to display!\nTry running the algorithm on the polygon!", MsgBoxType::Ok,
                   Falcor::MsgBoxIcon::Info);
        }

        return true;
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

void VisualEditor::showGui()
{
    mpEditor->publishEvent(ShowGuiPublishedEvent::create(), this);
}

void VisualEditor::hideGui()
{
    mpEditor->publishEvent(HideGuiPublishedEvent::create(), this);
}
void VisualEditor::setActiveInputHandler(const MouseInputHandler::SharedPtr &pInputHandler)
{
    if (mpActiveInputHandler != pInputHandler)
    {
        mpActiveInputHandler = pInputHandler;
        mpActiveInputHandler->resetInputState();
    }
}
