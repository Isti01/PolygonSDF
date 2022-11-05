#include "TriangleSample.h"

FALCOR_EXPORT_D3D12_AGILITY_SDK

namespace
{
    constexpr std::array<TriangleSample::FullScreenTriangleVertex, 3> kFullScreenTriangleVertices{
        {
            {{-1, -1, 0}, {0, 0}},
            {{3, -1, 0}, {2, 0}},
            {{-1, 3, 0}, {0, 2}},
        }
    };
    constexpr std::array<uint32_t, 3> kFullScreenTriangleIndexes{{0, 1, 2}};
}

void TriangleSample::onGuiRender(Gui* pGui)
{
}

TriangleSample::ObjectData::SharedPtr TriangleSample::createTriangleObject() const
{
    uint32_t vertexCount = kFullScreenTriangleVertices.size();
    const uint32_t vbSize = sizeof(FullScreenTriangleVertex) * vertexCount;

    auto pVb = Buffer::create(
        vbSize,
        Buffer::BindFlags::Vertex,
        Buffer::CpuAccess::None,
        kFullScreenTriangleVertices.data()
    );
    FALCOR_ASSERT(pVb);

    uint32_t indexCount = kFullScreenTriangleIndexes.size();
    const uint32_t ibSize = sizeof(uint32_t) * indexCount;

    auto pIb = Buffer::create(
        vbSize,
        Buffer::BindFlags::Index,
        Buffer::CpuAccess::None,
        kFullScreenTriangleIndexes.data()
    );
    FALCOR_ASSERT(pIb);

    const auto pLayout = VertexLayout::create();
    const auto pBufferLayout = VertexBufferLayout::create();
    pBufferLayout->addElement("POS", 0, ResourceFormat::RGB32Float, 1, 0);
    pBufferLayout->addElement("TEX_COORDS", 12, ResourceFormat::RG32Float, 1, 1);
    pLayout->addBufferLayout(0, pBufferLayout);

    Vao::SharedPtr pVao = Vao::create(Vao::Topology::TriangleStrip, pLayout, {pVb}, pIb, ResourceFormat::R32Uint);
    FALCOR_ASSERT(pVao);

    return std::make_shared<ObjectData>(pVb, pIb, pVao, vertexCount, indexCount);
}

void TriangleSample::onLoad(RenderContext* pRenderContext)
{
    object = createTriangleObject();

    Program::Desc desc;
    desc.addShaderLibrary("Samples/TriangleSample/TriangleSample.slang")
        .vsEntry("vsMain")
        .psEntry("psMain");

    mpGraphicsState = GraphicsState::create();
    mpGraphicsState->setDepthStencilState(DepthStencilState::create(DepthStencilState::Desc().setDepthEnabled(true)));
    mpGraphicsState->setProgram(GraphicsProgram::create(desc));
    mpGraphicsState->setVao(object->pVao);
    mpProgramVars = GraphicsVars::create(mpGraphicsState->getProgram().get());
}

void TriangleSample::onFrameRender(RenderContext* pRenderContext, const Fbo::SharedPtr& pTargetFbo)
{
    constexpr float4 clearColor(0, 0, 0, 1);
    pRenderContext->clearFbo(pTargetFbo.get(), clearColor, 1.0f, 0, FboAttachmentType::All);
    mpGraphicsState->setFbo(pTargetFbo);
    pRenderContext->drawIndexed(mpGraphicsState.get(), mpProgramVars.get(), object->indexCount, 0, 0);
}


void TriangleSample::onShutdown()
{
}

bool TriangleSample::onKeyEvent(const KeyboardEvent& keyEvent)
{
    return false;
}

bool TriangleSample::onMouseEvent(const MouseEvent& mouseEvent)
{
    return false;
}

void TriangleSample::onHotReload(HotReloadFlags reloaded)
{
}

void TriangleSample::onResizeSwapChain(uint32_t width, uint32_t height)
{
}

int main(int argc, char** argv)
{
    TriangleSample::UniquePtr pRenderer = std::make_unique<TriangleSample>();

    SampleConfig config;
    config.windowDesc.title = "Triangle";
    config.windowDesc.resizableWindow = true;
    config.windowDesc.width = 1280;
    config.windowDesc.height = 720;

    Sample::run(config, pRenderer);

    return 0;
}
