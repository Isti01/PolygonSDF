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

void getMinDistanceToEdges(float2 coord, inout float minDistance)
{
    uint pointCount, _;
    points.GetDimensions(pointCount, _);
    for (uint i = 0; i < pointCount; i++)
    {
        minDistance = min(minDistance, distance(coord, points[i]));

    }
}

float segmentLengthSquared(float2 segment[2])
{
    float2 difference = segment[0] - segment[1];
    return dot(difference, difference);
}

void getMinDistanceToSegments(float2 coord, inout float minDistance)
{
    uint segmentCount, _;
    segments.GetDimensions(segmentCount, _);
    for (uint i = 0; i < segmentCount; i++)
    {
        float2 segment[2] = segments[i].endpoints;

        float lengthSquared = segmentLengthSquared(segment);
        if (lengthSquared == 0.0)
        {
            minDistance = min(minDistance, distance(coord, segment[0]));
        }
        else
        {
            const float t = max(0, min(1, dot(coord - segment[0], segment[1] - segment[0]) / lengthSquared));
            const float2 projection = segment[0] + t * (segment[1] - segment[0]); // Projection falls on the segment
            minDistance = min(minDistance, distance(coord, projection));
        }
    }
}

float4 psMain(VsOut vsOut, uint triangleIndex : SV_PrimitiveID) : SV_TARGET
{
    float minDistance = 999999999;

    getMinDistanceToEdges(vsOut.texCoords, minDistance);
    getMinDistanceToSegments(vsOut.texCoords, minDistance);

    return float4(float3(sqrt(minDistance)), 1);
}
