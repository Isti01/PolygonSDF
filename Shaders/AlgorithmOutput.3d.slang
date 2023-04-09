cbuffer Data
{
    float4x4 iTransform;
}

struct VsIn
{
    float2 vertexPos : POS;
    float signedDistance : DST;
};

struct VsOut
{
    float4 vertexPos : SV_POSITION;
    float signedDistance: DST;
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

float4 signedDistanceToColor(float distance)
{
    float3 col = float3(1) - sign(distance) * float3(0.1, 0.4, 0.7);
    col *= 1 - exp(-4 * abs(distance));
    col *= 0.7 + 0.2 * cos(110 * distance);
    col = lerp(col, float3(1), 1 - smoothstep(0, 0.015, abs(distance)));
    return float4(col, 1);
}

PsOut psMain(VsOut vsOut, uint triangleIndex : SV_PrimitiveID) : SV_TARGET
{
    PsOut psOut;
    psOut.color = signedDistanceToColor(vsOut.signedDistance);
    psOut.depth = vsOut.signedDistance;
    return psOut;
}
