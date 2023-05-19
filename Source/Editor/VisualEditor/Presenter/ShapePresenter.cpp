#include "ShapePresenter.h"
#include "../../../Util/CoordinateUtil.h"
#include "../../../Util/Deferred.h"

using namespace Falcor;
using namespace psdf;

ShapePresenter::SharedPtr ShapePresenter::create(Editor::SharedPtr pEditor, ShapeRenderer::SharedPtr pRenderer)
{
    return SharedPtr(new ShapePresenter(std::move(pEditor), std::move(pRenderer)));
}

ShapePresenter::ShapePresenter(Editor::SharedPtr pEditor, ShapeRenderer::SharedPtr pRenderer)
    : Presenter(std::move(pEditor), std::move(pRenderer))
{
}

void ShapePresenter::render(RenderContext *pRenderContext, const Fbo::SharedPtr &pTargetFbo)
{
    updateShape();
    if (!mpShape)
    {
        return;
    }

    mpRenderer->setFbo(pTargetFbo);
    mpRenderer->render(pRenderContext);
}

bool ShapePresenter::onMouseEvent(const MouseEvent &mouseEvent)
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

void ShapePresenter::transformPresenter()
{
    auto translation = rmcv::translate(-float3(mTranslation, 0));

    float mappedScale = getMappedScale();
    auto scaling = rmcv::scale(float3{mappedScale, mappedScale, 1});
    auto transform = scaling * translation;
    mpRenderer->transform(transform);
}
