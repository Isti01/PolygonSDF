#include "DistanceVisualization.slang"

cbuffer Data
{
    float4x4 iTransform;
    float iDepthScaling;
}

struct VsIn
{
    float2 regionVertex : RV;
    float2 vertexPos : POS;
    float signedDistance : DST;
};

struct VsOut
{
    nointerpolation float2 regionVertex : RV;
    float2 samplePos : POS;
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
    vsOut.regionVertex = input.regionVertex;
    vsOut.samplePos = input.vertexPos;
    return vsOut;
}

PsOut psMain(VsOut vsOut, uint triangleIndex : SV_PrimitiveID) : SV_TARGET
{
    DistanceDesc desc;
    float dst = distance(vsOut.regionVertex, vsOut.samplePos);
    desc.distance = dst * sign(vsOut.signedDistance);
    desc.closerToVertex = false;

    PsOut psOut;
    psOut.color = signedDistanceToColor(desc);
    psOut.depth = dst / iDepthScaling;
    return psOut;
}
