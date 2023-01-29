#include "PolygonPresenter.h"
#include "../Event/NewStackCommandEvent.h"

using namespace Falcor;
using namespace psdf;

PolygonPresenter::SharedPtr PolygonPresenter::create()
{
    return SharedPtr(new PolygonPresenter());
}

void psdf::PolygonPresenter::accept(const psdf::EditorEvent::SharedPtr &pEvent)
{
    if (auto newCommandEvent = std::dynamic_pointer_cast<NewStackCommandEvent>(pEvent))
    {
        updatePolygon(newCommandEvent->getEditor()->getEditorStack()->peekPolygon());
    }
}

void PolygonPresenter::render(RenderContext *pRenderContext, const Fbo::SharedPtr &pTargetFbo)
{
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

void PolygonPresenter::updatePolygon(const Polygon::SharedPtr &pPolygon)
{
    mpPolygon = pPolygon;
    mpRenderer->setPolygon(pPolygon);
}
