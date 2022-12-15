#pragma once

#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

struct RenderObject
{
    using SharedPtr = std::shared_ptr<RenderObject>;
    Buffer::SharedPtr pVertexBuffer;
    Buffer::SharedPtr pIndexBuffer;
    Vao::SharedPtr pVao;

    uint32_t vertexCount;
    uint32_t indexCount;

    RenderObject(Buffer::SharedPtr pVertexBuffer, Buffer::SharedPtr pIndexBuffer, Vao::SharedPtr pVao,
                 uint32_t vertexCount, uint32_t indexCount)
        : pVertexBuffer(std::move(pVertexBuffer)), pIndexBuffer(std::move(pIndexBuffer)), pVao(std::move(pVao)),
          vertexCount(vertexCount), indexCount(indexCount)
    {
    }

    static SharedPtr create(const Buffer::SharedPtr &pVertexBuffer, const Buffer::SharedPtr &pIndexBuffer,
                            const Vao::SharedPtr &pVao, uint32_t vertexCount, uint32_t indexCount)
    {
        return std::make_shared<RenderObject>(pVertexBuffer, pIndexBuffer, pVao, vertexCount, indexCount);
    }

    template <typename VertexT>
    static SharedPtr create(const std::vector<VertexT> &vertices, const std::vector<uint32_t> indices,
                            const VertexLayout::SharedPtr &layout, Vao::Topology topology = Vao::Topology::TriangleList)
    {
        uint32_t vertexCount = vertices.size();
        const uint32_t vbSize = sizeof(VertexT) * vertexCount;

        auto pVb = Buffer::create(vbSize, Buffer::BindFlags::Vertex, Buffer::CpuAccess::None, vertices.data());
        FALCOR_ASSERT(pVb)

        uint32_t indexCount = indices.size();
        const uint32_t ibSize = sizeof(uint32_t) * indexCount;

        auto pIb = Buffer::create(ibSize, Buffer::BindFlags::Index, Buffer::CpuAccess::None, indices.data());
        FALCOR_ASSERT(pIb)

        Vao::SharedPtr pVao = Vao::create(topology, layout, {pVb}, pIb, ResourceFormat::R32Uint);
        FALCOR_ASSERT(pVao)

        return std::make_shared<psdf::RenderObject>(pVb, pIb, pVao, vertexCount, indexCount);
    }
};

} // namespace psdf
