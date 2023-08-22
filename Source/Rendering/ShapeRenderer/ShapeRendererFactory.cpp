#include "ShapeRendererFactory.h"
#include "Impl/AspectRatioIndependentShapeRenderer.h"
#include "Impl/CompositeShapeRenderer.h"
#include "Impl/FullScreenShapeRenderer.h"
#include "Impl/SdfAlgorithmEdgeRegionRenderer.h"
#include "Impl/ShapeOutlineRenderer.h"
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

ShapeRenderer::SharedPtr ShapeRendererFactory::getEditorShapeRenderer()
{
    auto combinedRenderers = CompositeShapeRenderer::create(std::vector<ShapeRenderer::SharedPtr>{
        FullScreenShapeRenderer::create(getFullscreenRendererGS()),
        ShapeOutlineRenderer::create(getOutlineRendererGS()),
    });
    auto renderer = AspectRatioIndependentShapeRenderer::create(combinedRenderers);
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

ShapeRenderer::SharedPtr ShapeRendererFactory::getAlgorithmOutputRenderer()
{
    auto combined = CompositeShapeRenderer::create({
        SdfAlgorithmEdgeRegionRenderer::create(
            getGraphicsStateForAlgorithmOutputRenderer(
                "PolygonSDF/Shaders/ModifiedDepthEdgeRegionAlgorithmOutput.3d.slang"),
            getGraphicsStateForAlgorithmOutputRenderer(
                "PolygonSDF/Shaders/SimpleMeshEdgeRegionAlgorithmOutput.3d.slang")),
        SdfAlgorithmVertexRegionRenderer::create(
            getGraphicsStateForAlgorithmOutputRenderer(
                "PolygonSDF/Shaders/ModifiedDepthVertexRegionAlgorithmOutput.3d.slang"),
            getGraphicsStateForAlgorithmOutputRenderer(
                "PolygonSDF/Shaders/SimpleMeshVertexRegionAlgorithmOutput.3d.slang")),
        ShapeOutlineRenderer::create(getOutlineRendererGS()),
    });
    auto renderer = AspectRatioIndependentShapeRenderer::create(combined);
    for (const auto &property : RendererProperties::kInitialProperties)
    {
        renderer->setProperty(property);
    }
    return renderer;
}
