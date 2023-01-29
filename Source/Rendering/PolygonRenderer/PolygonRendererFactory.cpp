#include "PolygonRendererFactory.h"
#include "Impl/AspectRatioIndependentPolygonRenderer.h"
#include "Impl/CompositePolygonRenderer.h"
#include "Impl/FullScreenPolygonRenderer.h"
#include "Impl/PolygonOutlineRenderer.h"

using namespace Falcor;
using namespace psdf;

static GraphicsState::SharedPtr getFullscreenRendererGS()
{
    auto pGraphicsState = GraphicsState::create();

    pGraphicsState->setDepthStencilState(DepthStencilState::create(DepthStencilState::Desc().setDepthEnabled(false)));
    pGraphicsState->setProgram(
        GraphicsProgram::create(Program::Desc()
                                    .addShaderLibrary("PolygonSDF/Shaders/NaivePolygonDistance.3d.slang")
                                    .vsEntry("vsMain")
                                    .psEntry("psMain")));

    return pGraphicsState;
}

static GraphicsState::SharedPtr getOutlineRendererGS()
{
    auto pGraphicsState = GraphicsState::create();

    pGraphicsState->setDepthStencilState(DepthStencilState::create(DepthStencilState::Desc().setDepthEnabled(false)));
    auto pBlendState = BlendState::create(BlendState::Desc().setRtBlend(0, true).setRtParams(
        0, BlendState::BlendOp::Add, BlendState::BlendOp::Add, BlendState::BlendFunc::SrcAlpha,
        BlendState::BlendFunc::OneMinusSrcAlpha, BlendState::BlendFunc::One, BlendState::BlendFunc::One));
    pGraphicsState->setBlendState(pBlendState);
    pGraphicsState->setProgram(GraphicsProgram::create(Program::Desc()
                                                           .addShaderLibrary("PolygonSDF/Shaders/SolidColor.3d.slang")
                                                           .vsEntry("vsMain")
                                                           .psEntry("psMain")));

    return pGraphicsState;
}

PolygonRenderer::SharedPtr PolygonRendererFactory::getPolygonRenderer()
{
    auto combinedRenderers = CompositePolygonRenderer::create(std::vector<PolygonRenderer::SharedPtr>{
        std::static_pointer_cast<PolygonRenderer>(FullScreenPolygonRenderer::create(getFullscreenRendererGS())),
        std::static_pointer_cast<PolygonRenderer>(
            PolygonOutlineRenderer::create(getOutlineRendererGS(), float4(1, 0, 0, 1))),
    });
    return std::static_pointer_cast<PolygonRenderer>(AspectRatioIndependentPolygonRenderer::create(combinedRenderers));
}
