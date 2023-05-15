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
    : Presenter(std::move(pEditor), std::move(pRenderer))
{
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
        transformPresenter();
        return true;
    }

    if (mpDragHandler->onMouseEvent(mouseEvent))
    {
        auto transform = mpRenderer->getTransform();
        auto delta = mpDragHandler->getDragDelta() * mTranslationSpeed;
        auto mappedCurrentPos = CoordinateUtil::screenToSceneSpaceCoordinate(transform, mouseEvent.pos);
        auto mappedLastPos = CoordinateUtil::screenToSceneSpaceCoordinate(transform, mouseEvent.pos - delta);
        auto mappedDelta = mappedCurrentPos - mappedLastPos;
        mTranslation += float2(mappedDelta.x, -mappedDelta.y);
        transformPresenter();
        return true;
    }

    return false;
}

void PolygonPresenter::transformPresenter()
{
    auto translation = rmcv::translate(-float3(mTranslation, 0));

    float mappedScale = getMappedScale();
    auto scaling = rmcv::scale(float3{mappedScale, mappedScale, 1});
    auto transform = scaling * translation;
    mpRenderer->transform(transform);
}
