#include "Presenter.h"

using namespace psdf;
using namespace Falcor;

Presenter::Presenter(Editor::SharedPtr pEditor, PolygonRenderer::SharedPtr outputRenderer)
    : mpDragHandler(DragMouseInputHandler::create()), mpEditor(std::move(pEditor)),
      mpPolygonPeekingAggregator(StackPeekingEditorAggregator::create()), mpRenderer(std::move(outputRenderer))
{
}

void Presenter::resetTransform()
{
    updatePolygon();
    mRotation = float2{0};
    mScale = mpPolygon ? 4 - glm::log2(sqrt(float(mpPolygon->getCircumscribedCircleRadiusFromCenter()))) : 4;
    mTranslation = mpPolygon ? float2(mpPolygon->getCenter()) : float2{0, 0};
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

void Presenter::updatePolygon()
{
    auto pResult = mpPolygonPeekingAggregator->peekEditor(mpEditor);
    FALCOR_ASSERT(pResult);

    auto pPolygon = pResult->getEntry().polygon;
    if (mpPolygon.get() == pPolygon.get())
    {
        return;
    }

    bool wasNull = pPolygon == nullptr;
    mpPolygon = pPolygon;
    mpRenderer->setPolygon(mpPolygon);
    if (wasNull)
    {
        transformPresenter();
    }
}
