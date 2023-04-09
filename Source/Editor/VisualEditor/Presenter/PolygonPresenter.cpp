#include "PolygonPresenter.h"
#include "../../../Util/CoordinateUtil.h"
#include "../../../Util/Deferred.h"

using namespace Falcor;
using namespace psdf;

PolygonPresenter::SharedPtr PolygonPresenter::create(Editor::SharedPtr pEditor, PolygonRenderer::SharedPtr pRenderer)
{
    return SharedPtr(new PolygonPresenter(std::move(pEditor), std::move(pRenderer)));
}

PolygonPresenter::PolygonPresenter(Editor::SharedPtr pEditor, PolygonRenderer::SharedPtr pRenderer)
    : mpEditor(std::move(pEditor)), mpRenderer(std::move(pRenderer)),
      mpPolygonPeekingAggregator(StackPeekingEditorAggregator::create()), mpDragHandler(DragMouseInputHandler::create())
{
    transformPolygonRenderer();
}

void PolygonPresenter::render(RenderContext *pRenderContext, const Fbo::SharedPtr &pTargetFbo)
{
    updatePolygon();
    if (!mpPolygon)
    {
        return;
    }

    mpRenderer->setFbo(pTargetFbo);
    mpRenderer->render(pRenderContext);
}

bool PolygonPresenter::onMouseEvent(const MouseEvent &mouseEvent)
{
    if (mouseEvent.type == MouseEvent::Type::Wheel)
    {
        mScale += mouseEvent.wheelDelta.y * mScaleSpeed;
        transformPolygonRenderer();
        return true;
    }

    if (mpDragHandler->onMouseEvent(mouseEvent))
    {
        auto transform = mpRenderer->getTransform();
        auto delta = (mpDragHandler->getDragDelta() * mTranslationSpeed) * getMappedScale();
        mTranslation += CoordinateUtil::screenToSceneSpaceVector(transform, delta);
        transformPolygonRenderer();
        return true;
    }

    return false;
}

void PolygonPresenter::resetInputState()
{
    mpDragHandler->resetInputState();
}

void PolygonPresenter::updatePolygon()
{
    auto pResult = mpPolygonPeekingAggregator->peekEditor(mpEditor);
    FALCOR_ASSERT(pResult);

    auto pPolygon = pResult->getEntry().polygon;
    if (mpPolygon.get() == pPolygon.get())
    {
        return;
    }

    mpPolygon = pPolygon;

    if (mpPolygon != nullptr)
    {
        mpRenderer->setPolygon(pPolygon);
    }
}

float PolygonPresenter::getMappedScale() const
{
    return glm::pow(2.0f, mScale);
}

void PolygonPresenter::transformPolygonRenderer()
{
    auto translation = rmcv::translate(float3(mTranslation, 0));

    float mappedScale = getMappedScale();
    auto scaling = rmcv::scale(float3{mappedScale, mappedScale, 1});
    mpRenderer->transform(translation * scaling);
}
