#include "PolygonPresenter.h"
#include "../Aggregator/PolygonPeekingEditorAggregator.h"

using namespace Falcor;
using namespace psdf;

PolygonPresenter::SharedPtr PolygonPresenter::create(Editor::SharedPtr pEditor)
{
    return SharedPtr(new PolygonPresenter(std::move(pEditor)));
}

PolygonPresenter::PolygonPresenter(Editor::SharedPtr pEditor)
    : mpEditor(std::move(pEditor)), mpPolygonPeekingAggregator(PolygonPeekingEditorAggregator::create())
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

void PolygonPresenter::setRenderer(const PolygonRenderer::SharedPtr &pRenderer)
{
    mpRenderer = pRenderer;
}

void PolygonPresenter::updatePolygon()
{
    auto pResult = mpPolygonPeekingAggregator->peekEditor(mpEditor);
    FALCOR_ASSERT(pResult);

    auto pPolygon = pResult->getPolygon();
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
