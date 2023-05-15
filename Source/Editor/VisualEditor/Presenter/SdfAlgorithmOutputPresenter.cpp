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
    : Presenter(std::move(pEditor), std::move(outputRenderer))
{
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
        mRotation += mpDragHandler->getDragDelta() * mRotationSpeed;
        transformPresenter();
        return true;
    }

    return false;
}

void SdfAlgorithmOutputPresenter::transformPresenter()
{
    auto rotation = rmcv::rotate(mRotation.x, {0, 1, 0}) * rmcv::rotate(mRotation.y, {1, 0, 0});
    auto scaling = rmcv::scale(float3{getMappedScale()});
    auto translation = rmcv::translate(-float3{mTranslation, 0});
    mpRenderer->transform(rotation * scaling * translation);
}
