#include "SdfAlgorithmOutputPresenter.h"
#include "../../../Util/CoordinateUtil.h"

using namespace psdf;
using namespace Falcor;

SdfAlgorithmOutputPresenter::SharedPtr SdfAlgorithmOutputPresenter::create(Editor::SharedPtr pEditor,
                                                                           PolygonRenderer::SharedPtr outputRenderer)
{
    return SharedPtr(new SdfAlgorithmOutputPresenter(std::move(pEditor), std::move(outputRenderer)));
}

SdfAlgorithmOutputPresenter::SdfAlgorithmOutputPresenter(Editor::SharedPtr pEditor,
                                                         PolygonRenderer::SharedPtr outputRenderer)
    : mpEditor(std::move(pEditor)), mpPolygonPeekingAggregator(StackPeekingEditorAggregator::create()),
      mpDragHandler(DragMouseInputHandler::create()), mpRenderer(std::move(outputRenderer))
{
    transformPresenter();
}

void SdfAlgorithmOutputPresenter::render(RenderContext *pRenderContext, const Fbo::SharedPtr &pTargetFbo)
{
    updatePolygon();
    if (!mpPolygon || !mpPolygon->getAlgorithmOutput())
    {
        return;
    }

    mpRenderer->setFbo(pTargetFbo);
    mpRenderer->render(pRenderContext);
}

bool SdfAlgorithmOutputPresenter::onMouseEvent(const MouseEvent &mouseEvent)
{
    if (mouseEvent.type == MouseEvent::Type::Wheel)
    {
        mScale += mouseEvent.wheelDelta.y * mScaleSpeed;
        transformPresenter();
        return true;
    }

    if (mpDragHandler->onMouseEvent(mouseEvent))
    {
        float mappedScale = getMappedScale();
        auto transform = rmcv::scale(float3{mappedScale, mappedScale, 1});
        auto delta = (mpDragHandler->getDragDelta() * mRotationSpeed) * getMappedScale();
        mRotation += CoordinateUtil::screenToSceneSpaceVector(transform, delta) * mRotationSpeed;
        transformPresenter();
        return true;
    }

    return false;
}

void SdfAlgorithmOutputPresenter::resetInputState()
{
    resetTransform();
    mpDragHandler->resetInputState();
}

void SdfAlgorithmOutputPresenter::updatePolygon()
{
    auto pResult = mpPolygonPeekingAggregator->peekEditor(mpEditor);
    FALCOR_ASSERT(pResult);

    auto pPolygon = pResult->getEntry().polygon;
    if (mpPolygon.get() == pPolygon.get())
    {
        return;
    }

    mpPolygon = pPolygon;
    mpRenderer->setPolygon(mpPolygon);
}

void SdfAlgorithmOutputPresenter::resetTransform()
{
    mScale = 3.5;
    mRotation = float2{0};
    transformPresenter();
}

float SdfAlgorithmOutputPresenter::getMappedScale() const
{
    return glm::pow(2.0f, mScale);
}

void SdfAlgorithmOutputPresenter::transformPresenter()
{
    auto rotation = rmcv::rotate(mRotation.x, {0, 1, 0}) * rmcv::rotate(mRotation.y, {1, 0, 0});

    float mappedScale = getMappedScale();
    auto scaling = rmcv::scale(float3{-mappedScale, mappedScale, mappedScale});
    mpRenderer->transform(rotation * scaling);
}
