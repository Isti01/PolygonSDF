#include "Common.slang"

cbuffer Data
{
    float4x4 iTransform;
}

struct Segment
{
    float2 point1;
    float2 point2;
};

StructuredBuffer<Segment> segments;

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

DistanceDesc getSignedSquaredDistance(float2 coord)
{
    bool closerToVertex = false;
    float squaredDistance = dot(coord - segments[0].point1, coord - segments[0].point1);
    float distanceSign = 1;

    uint segmentCount, _;
    segments.GetDimensions(segmentCount, _);

    for (int i = 0; i < segmentCount; i++)
    {
        float2 e = segments[i].point1 - segments[i].point2;
        float2 w = coord - segments[i].point2;
        float p = dot(w, e) / dot(e, e);
        float2 b = w - e * saturate(p);
        float distance = dot(b, b);
        if (distance < squaredDistance)
        {
            squaredDistance = distance;
            closerToVertex = p >= 0 && p <= 1;
        }
        bool3 winding = bool3(coord.y >= segments[i].point2.y, coord.y<segments[i].point1.y, e.x * w.y> e.y * w.x);
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

float4 psMain(VsOut vsOut, uint triangleIndex: SV_PrimitiveID) : SV_TARGET
{
    DistanceDesc desc = getSignedSquaredDistance(vsOut.texCoords);
    return signedDistanceToColor(desc);
}
