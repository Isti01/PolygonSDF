#pragma once

#include <Falcor.h>
#include <utility>

using namespace Falcor;

namespace psdf
{

class PolygonSDF : public IRenderer
{
  public:
    struct ObjectData
    {
        using SharedPtr = std::shared_ptr<ObjectData>;
        Buffer::SharedPtr pVertexBuffer;
        Buffer::SharedConstPtr pIndexBuffer;
        Vao::SharedPtr pVao;

        uint32_t vertexCount;
        uint32_t indexCount;

        ObjectData(Buffer::SharedPtr pVertexBuffer, Buffer::SharedConstPtr pIndexBuffer, Vao::SharedPtr pVao,
                   uint32_t vertexCount, uint32_t indexCount)
            : pVertexBuffer(std::move(pVertexBuffer)), pIndexBuffer(std::move(pIndexBuffer)), pVao(std::move(pVao)),
              vertexCount(vertexCount), indexCount(indexCount)
        {
        }

        static SharedPtr create(const Buffer::SharedPtr &pVertexBuffer, const Buffer::SharedConstPtr &pIndexBuffer,
                                const Vao::SharedPtr &pVao, uint32_t vertexCount, uint32_t indexCount)
        {
            return std::make_shared<ObjectData>(pVertexBuffer, pIndexBuffer, pVao, vertexCount, indexCount);
        }
    };

    struct FullScreenTriangleVertex
    {
        float3 pos;
        float2 texCoords;
    };

  public:
    void onLoad(RenderContext *pRenderContext) override;
    [[nodiscard]] ObjectData::SharedPtr createTriangleObject() const;
    void onFrameRender(RenderContext *pRenderContext, const Fbo::SharedPtr &pTargetFbo) override;
    void onShutdown() override;
    void onResizeSwapChain(uint32_t width, uint32_t height) override;
    bool onKeyEvent(const KeyboardEvent &keyEvent) override;
    bool onMouseEvent(const MouseEvent &mouseEvent) override;
    void onHotReload(HotReloadFlags reloaded) override;
    void onGuiRender(Gui *pGui) override;

  private:
    GraphicsVars::SharedPtr mpProgramVars = nullptr;
    GraphicsState::SharedPtr mpGraphicsState = nullptr;

    ObjectData::SharedPtr object = nullptr;
};

} // namespace psdf
