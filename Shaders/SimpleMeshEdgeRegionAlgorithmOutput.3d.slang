#include "DistanceVisualization.slang"

cbuffer Data
{
    float4x4 iTransform;
    float iDepthScaling;
}

struct VsIn
{
    float2 vertexPos : POS;
    float signedDistance : DST;
};

struct VsOut
{
    float4 vertexPos : SV_POSITION;
    float signedDistance : DST;
};

struct PsOut
{
    float4 color : SV_TARGET;
    float depth : SV_DEPTH;
};

VsOut vsMain(VsIn input)
{
    VsOut vsOut;
    vsOut.vertexPos = mul(iTransform, float4(input.vertexPos, abs(input.signedDistance), 1));
    vsOut.signedDistance = input.signedDistance;
    return vsOut;
}

PsOut psMain(VsOut vsOut, uint triangleIndex : SV_PrimitiveID) : SV_TARGET
{
    DistanceDesc desc;
    desc.closerToVertex = true;
    desc.distance = vsOut.signedDistance;

    PsOut psOut;
    psOut.color = signedDistanceToColor(desc);
    psOut.depth = abs(vsOut.signedDistance) / iDepthScaling;
    return psOut;
}
