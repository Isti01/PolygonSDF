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
    vsOut.texCoords = input.texCoords;
    return vsOut;
}

float4 psMain(VsOut vsOut, uint triangleIndex : SV_PrimitiveID) : SV_TARGET
{
    return float4(vsOut.texCoords.rg, 0, 1);
}
