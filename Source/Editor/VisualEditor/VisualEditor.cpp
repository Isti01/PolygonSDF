#include "VisualEditor.h"
#include "../../Rendering/PolygonRenderer/PolygonRendererFactory.h"
#include "../PublishedEvent/HideGuiPublishedEvent.h"
#include "../PublishedEvent/ShowGuiPublishedEvent.h"
#include "../PublishedEvent/VisualEditorModeChangedPublishedEvent.h"
#include "Input/MoveInputHandler.h"

using namespace psdf;

VisualEditor::SharedPtr VisualEditor::create(Editor::SharedPtr pEditor)
{
    return SharedPtr(new VisualEditor(std::move(pEditor)));
}

VisualEditor::VisualEditor(Editor::SharedPtr pEditor)
    : mpEditor(std::move(pEditor)), mpEditorPolygonRenderer(PolygonRendererFactory::getPolygonRenderer()),
      mpAlgorithmPolygonRenderer(PolygonRendererFactory::getAlgorithmOutputRenderer()),
      mpEditorRendererUpdatingConsumer(PropertyUpdatingEditorConsumer::create(mpEditorPolygonRenderer)),
      mpAlgorithmRendererUpdatingConsumer(PropertyUpdatingEditorConsumer::create(mpAlgorithmPolygonRenderer)),
      mpPolygonPresenter(PolygonPresenter::create(mpEditor, mpEditorPolygonRenderer)),
      mpVertexMover(MoveInputHandler::create(PointUpdateMoveStrategy::create(), mpEditor, mpEditorPolygonRenderer)),
      mpGroupMover(MoveInputHandler::create(GroupMoveStrategy::create(), mpEditor, mpEditorPolygonRenderer)),
      mpVertexInserter(InsertRemoveVertexInputHandler::create(mpEditor, mpEditorPolygonRenderer)),
      mpActiveInputHandler(mpPolygonPresenter), mpStackPeekingAggregator(StackPeekingEditorAggregator::create()),
      mpAlgorithmOutputPresenter(SdfAlgorithmOutputPresenter::create(mpEditor, mpAlgorithmPolygonRenderer))
{
    mpEditor->publishEvent(VisualEditorModeChangedPublishedEvent::create("V - Pan and Zoom"), this);
    mpEditor->addConsumer(mpEditorRendererUpdatingConsumer);
    mpEditor->addConsumer(mpAlgorithmRendererUpdatingConsumer);
}

VisualEditor::~VisualEditor()
{
    mpEditor->removeConsumer(mpEditorRendererUpdatingConsumer);
    mpEditor->removeConsumer(mpAlgorithmRendererUpdatingConsumer);
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
        mpEditor->publishEvent(VisualEditorModeChangedPublishedEvent::create("M - Move Vertices"), this);
        return true;
    }

    if (keyEvent.key == Input::Key::G)
    {
        showGui();
        setActiveInputHandler(mpGroupMover);
        mpEditor->publishEvent(VisualEditorModeChangedPublishedEvent::create("G - Move Groups"), this);
        return true;
    }

    if (keyEvent.key == Input::Key::V)
    {
        showGui();
        setActiveInputHandler(mpPolygonPresenter);
        mpEditor->publishEvent(VisualEditorModeChangedPublishedEvent::create("V - Pan and Zoom"), this);
        return true;
    }

    if (keyEvent.key == Input::Key::I)
    {
        showGui();
        setActiveInputHandler(mpVertexInserter);
        mpEditor->publishEvent(VisualEditorModeChangedPublishedEvent::create("I - Insert vertices"), this);
        return true;
    }

    if (keyEvent.key == Input::Key::D)
    {
        auto pPolygon = mpStackPeekingAggregator->peekEditor(mpEditor)->getEntry().polygon;
        if (pPolygon && pPolygon->getAlgorithmOutput())
        {
            hideGui();
            setActiveInputHandler(mpAlgorithmOutputPresenter);
            mpEditor->publishEvent(VisualEditorModeChangedPublishedEvent::create("D - View algorithm result"), this);
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
    if (mpActiveInputHandler == pInputHandler)
    {
        return;
    }

    if (mpActiveInputHandler.get() == mpAlgorithmOutputPresenter.get() ||
        pInputHandler.get() == mpAlgorithmOutputPresenter.get())
    {
        mpAlgorithmOutputPresenter->resetTransform();
        mpPolygonPresenter->resetTransform();
    }
    mpActiveInputHandler = pInputHandler;
    mpActiveInputHandler->resetInputState();
}
