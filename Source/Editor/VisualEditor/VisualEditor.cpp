#include "VisualEditor.h"
#include "../../Rendering/ShapeRenderer/ShapeRendererFactory.h"
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
    : mpEditor(std::move(pEditor)), mpEditorShapeRenderer(ShapeRendererFactory::getEditorShapeRenderer()),
      mpAlgorithmOutputRenderer(ShapeRendererFactory::getAlgorithmOutputRenderer()),
      mpEditorRendererUpdatingConsumer(PropertyUpdatingEditorConsumer::create(mpEditorShapeRenderer)),
      mpAlgorithmRendererUpdatingConsumer(PropertyUpdatingEditorConsumer::create(mpAlgorithmOutputRenderer)),
      mpShapePresenter(ShapePresenter::create(mpEditor, mpEditorShapeRenderer)),
      mpVertexMover(MoveInputHandler::create(PointUpdateMoveStrategy::create(), mpEditor, mpEditorShapeRenderer)),
      mpOutlineMover(MoveInputHandler::create(OutlineMoveStrategy::create(), mpEditor, mpEditorShapeRenderer)),
      mpVertexInserter(InsertRemoveVertexInputHandler::create(mpEditor, mpEditorShapeRenderer)),
      mpActiveInputHandler(mpShapePresenter), mpStackPeekingAggregator(StackPeekingEditorAggregator::create()),
      mpAlgorithmOutputPresenter(SdfAlgorithmOutputPresenter::create(mpEditor, mpAlgorithmOutputRenderer))
{
    mpEditor->publishEvent(VisualEditorModeChangedPublishedEvent::create("V - Pan and Zoom"), this);
    mpEditor->addConsumer(mpEditorRendererUpdatingConsumer);
    mpEditor->addConsumer(mpAlgorithmRendererUpdatingConsumer);
    mpAlgorithmOutputPresenter->resetTransform();
    mpShapePresenter->resetTransform();
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
        mpShapePresenter->render(pRenderContext, pTargetFbo);
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
        setActiveInputHandler(mpOutlineMover);
        mpEditor->publishEvent(VisualEditorModeChangedPublishedEvent::create("G - Move Outlines"), this);
        return true;
    }

    if (keyEvent.key == Input::Key::V)
    {
        showGui();
        setActiveInputHandler(mpShapePresenter);
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
        auto pShape = mpStackPeekingAggregator->peekEditor(mpEditor)->getEntry().pShape;
        if (pShape && pShape->getAlgorithmOutput())
        {
            hideGui();
            setActiveInputHandler(mpAlgorithmOutputPresenter);
            mpEditor->publishEvent(VisualEditorModeChangedPublishedEvent::create("D - View algorithm result"), this);
        }
        else
        {
            msgBox("There is nothing to display!\nTry running the algorithm on the shape!", MsgBoxType::Ok,
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
        mpShapePresenter->resetTransform();
    }
    mpActiveInputHandler = pInputHandler;
    mpActiveInputHandler->resetInputState();
}
