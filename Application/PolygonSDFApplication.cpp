#include "PolygonSDFApplication.h"
#include "../Source/Editor/Command/SetShapeStackCommand.h"
#include "../Source/Editor/Constraint/DeleteOutlineEditorConstraint.h"
#include "../Source/Editor/Constraint/DeleteVertexEditorConstraint.h"
#include "../Source/Editor/Constraint/SdfPlaneAlgorithmConstraint.h"

#include <memory>

using namespace Falcor;
using namespace psdf;

void PolygonSDFApplication::onLoad(RenderContext *pRenderContext)
{
    mpEditor = Editor::create(EditorStack::create());
    mpEditor->addCommand(SetShapeStackCommand::create(Shape::kStarterShape));
    mpGuiEditor = GuiEditor::create(mpEditor);
    mpVisualEditor = VisualEditor::create(mpEditor);
    mpEditor->addConstraint(DeleteOutlineEditorConstraint::create());
    mpEditor->addConstraint(DeleteVertexEditorConstraint::create());
    mpEditor->addConstraint(SdfPlaneAlgorithmConstraint::create());
    mpGuiStateConsumer = GuiStateEditorConsumer::create();
    mpEditor->addConsumer(mpGuiStateConsumer);
}

void PolygonSDFApplication::onGuiRender(Gui *pGui)
{
    if (!mpGuiStateConsumer->isGuiEnabled())
    {
        return;
    }
    Gui::Window window(pGui, "PolygonSDF");
    mpGuiEditor->render(window);
}

void PolygonSDFApplication::onFrameRender(RenderContext *pRenderContext, const Fbo::SharedPtr &pTargetFbo)
{
    constexpr float4 clearColor(0, 0, 0, 1);
    pRenderContext->clearFbo(pTargetFbo.get(), clearColor, 1.0f, 0, FboAttachmentType::All);

    mpVisualEditor->render(pRenderContext, pTargetFbo);
}

bool PolygonSDFApplication::onKeyEvent(const KeyboardEvent &keyEvent)
{
    if (keyEvent.key == Input::Key::Escape)
    {
        return true;
    }
    return mpVisualEditor->onKeyEvent(keyEvent);
}

bool PolygonSDFApplication::onMouseEvent(const MouseEvent &mouseEvent)
{
    return mpVisualEditor->onMouseEvent(mouseEvent);
}

void PolygonSDFApplication::onShutdown()
{
    mpEditor->removeConsumer(mpGuiStateConsumer);
}
