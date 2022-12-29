cbuffer Data
{
    float4x4 iTransform;
}

struct Segment
{
    float2 endpoints[2];
};

StructuredBuffer<float2> points;

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

float getSignedSquaredDistance(float2 coord)
{
    float squaredDistance = dot(coord - points[0], coord - points[0]);
    float distanceSign = 1;

    uint pointCount, _;
    points.GetDimensions(pointCount, _);

    for (int i = 0, j = pointCount - 1; i < pointCount; j = i, i++)
    {
        float2 e = points[j] - points[i];
        float2 w = coord - points[i];
        float2 b = w - e * saturate(dot(w, e) / dot(e, e));
        squaredDistance = min(squaredDistance, dot(b, b));
        bool3 c = bool3(coord.y >= points[i].y, coord.y < points[j].y, e.x * w.y > e.y * w.x);
        if (all(c) || all(!c))
        {
            distanceSign *= -1.0;
        }
    }
    return distanceSign * sqrt(squaredDistance);
}

float4 visualizeSignedDistance(float distance)
{
    float3 col = float3(1) - sign(distance) * float3(0.1, 0.4, 0.7);
    col *= 1 - exp(-4 * abs(distance));
    col *= 0.7 + 0.2 * cos(110 * distance);
    col = lerp(col, float3(1), 1 - smoothstep(0, 0.015, abs(distance)));
    return float4(col, 1);
}

float4 psMain(VsOut vsOut, uint triangleIndex : SV_PrimitiveID) : SV_TARGET
{
    float distance = getSignedSquaredDistance(vsOut.texCoords);
    return visualizeSignedDistance(distance);
}
