struct DistanceDesc
{
    float distance;
    bool closerToVertex;
};

float4 signedDistanceToColor(DistanceDesc desc)
{
    float distance = desc.distance;
    float3 col = float3(1) - sign(distance) * float3(0.1, 0.4, 0.7);
    col *= 1 - exp(-4 * abs(distance));
    col *= 0.7 + 0.2 * cos(110 * distance);
    col = lerp(col, float3(1), 1 - smoothstep(0, 0.015, abs(distance)));
    if (desc.closerToVertex)
    {
        col *= .7;
    }
    return float4(col, 1);
}
