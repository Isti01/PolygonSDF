cbuffer Data
{
    float4x4 iTransform;
}

struct Segment
{
    float2 endpoints[2];
};

StructuredBuffer<float2> points;
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

float4 psMain(VsOut vsOut, uint triangleIndex : SV_PrimitiveID) : SV_TARGET
{
    float2 coords =  vsOut.texCoords;
    float minDistance = 999999999;

    uint pointCount, _;
    points.GetDimensions(pointCount, _);
    for (uint i = 0; i < pointCount; i++)
    {
        minDistance = min(minDistance, distance(coords, points[i]));

    }

    return float4(float3(minDistance), 1);
}
