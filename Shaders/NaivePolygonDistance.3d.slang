#include "DistanceVisualization.slang"

cbuffer Data
{
    float4x4 iTransform;
}

struct Edge
{
    float2 vertex1;
    float2 vertex2;
};

StructuredBuffer<Edge> edges;

struct VsIn
{
    float3 vertexPos : POS;
    float2 texCoords : TEX_COORDS;
};

struct VsOut
{
    float4 vertexPos : SV_POSITION;
    float2 texCoords : TEX_COORDS;
};

VsOut vsMain(VsIn input)
{
    VsOut vsOut;
    vsOut.vertexPos = float4(input.vertexPos, 1);
    vsOut.texCoords = mul(iTransform, float4(input.texCoords, 0, 1)).xy;
    return vsOut;
}

DistanceDesc getSignedDistance(float2 coord)
{
    bool closerToVertex = false;
    float squaredDistance = dot(coord - edges[0].vertex1, coord - edges[0].vertex1);
    float distanceSign = 1;

    uint segmentCount, _;
    edges.GetDimensions(segmentCount, _);

    for (int i = 0; i < segmentCount; i++)
    {
        float2 e = edges[i].vertex1 - edges[i].vertex2;
        float2 w = coord - edges[i].vertex2;
        float p = dot(w, e) / dot(e, e);
        float2 b = w - e * saturate(p);
        float distance = dot(b, b);
        if (distance < squaredDistance)
        {
            squaredDistance = distance;
            closerToVertex = p >= 0 && p <= 1;
        }
        bool3 winding = bool3(coord.y >= edges[i].vertex2.y, coord.y<edges[i].vertex1.y, e.x * w.y> e.y * w.x);
        if (all(winding) || all(!winding))
        {
            distanceSign *= -1.0;
        }
    }

    DistanceDesc desc;
    desc.distance = distanceSign * sqrt(squaredDistance);
    desc.closerToVertex = closerToVertex;
    return desc;
}

float4 psMain(VsOut vsOut, uint triangleIndex : SV_PrimitiveID) : SV_TARGET
{
    DistanceDesc desc = getSignedDistance(vsOut.texCoords);
    return signedDistanceToColor(desc);
}
