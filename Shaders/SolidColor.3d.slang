cbuffer Data
{
    float4x4 iTransform;
    float4 iColor;
}

struct VsIn
{
    float2 vertexPos : POS;
};

struct VsOut
{
    float4 vertexPos : SV_POSITION;
};

VsOut vsMain(VsIn input)
{
    VsOut vsOut;
    vsOut.vertexPos = mul(iTransform, float4(input.vertexPos, 0, 1));
    return vsOut;
}

float4 psMain(VsOut vsOut, uint triangleIndex : SV_PrimitiveID) : SV_TARGET
{
    return iColor;
}
