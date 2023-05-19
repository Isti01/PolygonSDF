#include "Presenter.h"

using namespace psdf;
using namespace Falcor;

Presenter::Presenter(Editor::SharedPtr pEditor, ShapeRenderer::SharedPtr outputRenderer)
    : mpDragHandler(DragMouseInputHandler::create()), mpEditor(std::move(pEditor)),
      mpShapePeekingAggregator(StackPeekingEditorAggregator::create()), mpRenderer(std::move(outputRenderer))
{
}

void Presenter::resetTransform()
{
    updateShape();
    mRotation = float2{0};
    mScale = mpShape ? 4 - glm::log2(sqrt(float(mpShape->getCircumscribedCircleRadiusFromCenter()))) : 4;
    mTranslation = mpShape ? float2(mpShape->getCenter()) : float2{0, 0};
    transformPresenter();
}

float Presenter::getMappedScale() const
{
    return glm::pow(2.0f, mScale);
}

void Presenter::resetInputState()
{
    mpDragHandler->resetInputState();
}

void Presenter::updateShape()
{
    auto pResult = mpShapePeekingAggregator->peekEditor(mpEditor);
    FALCOR_ASSERT(pResult);

    auto pShape = pResult->getEntry().pShape;
    if (mpShape.get() == pShape.get())
    {
        return;
    }

    bool wasNull = pShape == nullptr;
    mpShape = pShape;
    mpRenderer->setShape(mpShape);
    if (wasNull)
    {
        transformPresenter();
    }
}
