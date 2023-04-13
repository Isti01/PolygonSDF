cbuffer Data
{
    float4x4 iTransform;
}

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

struct DistanceResult
{
    float distance;
    bool closerToVertex;
};

VsOut vsMain(VsIn input)
{
    VsOut vsOut;
    vsOut.vertexPos = float4(input.vertexPos, 1);
    vsOut.texCoords = mul(iTransform, float4(input.texCoords, 0, 1)).xy;
    return vsOut;
}

DistanceResult getSignedSquaredDistance(float2 coord)
{
    bool closerToVertex = false;
    float squaredDistance = dot(coord - points[0], coord - points[0]);
    float distanceSign = 1;

    uint pointCount, _;
    points.GetDimensions(pointCount, _);

    for (int i = 0, j = pointCount - 1; i < pointCount; j = i, i++)
    {
        float2 e = points[j] - points[i];
        float2 w = coord - points[i];
        float p = dot(w, e) / dot(e, e);
        float2 b = w - e * saturate(p);
        float distance = dot(b, b);
        if (distance < squaredDistance)
        {
            squaredDistance = distance;
            closerToVertex = p >= 0 && p <= 1;
        }
        bool3 winding = bool3(coord.y >= points[i].y, coord.y < points[j].y, e.x * w.y > e.y * w.x);
        if (all(winding) || all(!winding))
        {
            distanceSign *= -1.0;
        }
    }

    DistanceResult result;
    result.distance = distanceSign * sqrt(squaredDistance);
    result.closerToVertex = closerToVertex;
    return result;
}

float4 signedDistanceToColor(DistanceResult result)
{
    float distance = result.distance;
    float3 col = float3(1) - sign(distance) * float3(0.1, 0.4, 0.7);
    col *= 1 - exp(-4 * abs(distance));
    col *= 0.7 + 0.2 * cos(110 * distance);
    col = lerp(col, float3(1), 1 - smoothstep(0, 0.015, abs(distance)));
    if (result.closerToVertex)
    {
        col *= .7;
    }
    return float4(col, 1);
}

float4 psMain(VsOut vsOut, uint triangleIndex: SV_PrimitiveID) : SV_TARGET
{
    DistanceResult result = getSignedSquaredDistance(vsOut.texCoords);
    return signedDistanceToColor(result);
}
