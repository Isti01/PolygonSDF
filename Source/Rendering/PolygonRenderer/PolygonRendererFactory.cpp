#include "PolygonRendererFactory.h"
#include "Impl/AspectRatioIndependentPolygonRenderer.h"
#include "Impl/CompositePolygonRenderer.h"
#include "Impl/FullScreenPolygonRenderer.h"
#include "Impl/PolygonOutlineRenderer.h"
#include "Impl/SdfAlgorithmLineRegionRenderer.h"
#include "RendererProperties.h"

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
        FullScreenPolygonRenderer::create(getFullscreenRendererGS()),
        PolygonOutlineRenderer::create(getOutlineRendererGS()),
    });
    auto renderer = AspectRatioIndependentPolygonRenderer::create(combinedRenderers);
    for (const auto &property : RendererProperties::kInitialProperties)
    {
        renderer->setProperty(property);
    }
    return renderer;
}

static GraphicsState::SharedPtr getGraphicsStateForAlgorithmOutputRenderer(const char *shaderPath)
{
    auto pGraphicsState = GraphicsState::create();
    auto pRasterizerState =
        RasterizerState::create(RasterizerState::Desc().setCullMode(Falcor::RasterizerState::CullMode::None));
    pGraphicsState->setRasterizerState(pRasterizerState);

    pGraphicsState->setDepthStencilState(DepthStencilState::create(DepthStencilState::Desc().setDepthEnabled(true)));

    auto pProgram =
        GraphicsProgram::create(Program::Desc().addShaderLibrary(shaderPath).vsEntry("vsMain").psEntry("psMain"));
    pGraphicsState->setProgram(pProgram);
    return pGraphicsState;
}

PolygonRenderer::SharedPtr PolygonRendererFactory::getAlgorithmOutputRenderer()
{
    auto renderer = CompositePolygonRenderer::create({
        SdfAlgorithmLineRegionRenderer::create(
            getGraphicsStateForAlgorithmOutputRenderer("PolygonSDF/Shaders/LineRegionAlgorithmOutput.3d.slang")),
        SdfAlgorithmPointRegionRenderer::create(
            getGraphicsStateForAlgorithmOutputRenderer("PolygonSDF/Shaders/PointRegionAlgorithmOutput.3d.slang")),
    });
    for (const auto &property : RendererProperties::kInitialProperties)
    {
        renderer->setProperty(property);
    }
    return renderer;
}
