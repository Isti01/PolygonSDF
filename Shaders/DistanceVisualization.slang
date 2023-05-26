cbuffer DistanceColoringSettings
{
    float3 iPositiveColor;
    float3 iNegativeColor;
    float iContourFrequency;
    float iContourIntensity;
    bool iDisplayShadows;
    float iShadowIntensity;
    bool iDisplayCloserToVertex;
    bool iShouldDisplayContours;
    bool iShouldColorBetweenContours;
}

struct DistanceDesc
{
    float distance;
    bool closerToVertex;
};

float4 signedDistanceToColor(DistanceDesc desc)
{
    float distance = desc.distance;
    float3 col = (distance > 0.0) ? iPositiveColor : iNegativeColor;
    col *= 1.0 - exp(-iShadowIntensity * abs(distance)) * int(iDisplayShadows);
    float colorBetweenContours = (1 - iContourIntensity) * int(iShouldColorBetweenContours);
    float colorContour = iContourIntensity * cos(iContourFrequency * distance) * int(iShouldDisplayContours);
    col *= colorBetweenContours + colorContour;
    col = lerp(col, float3(1), 1 - smoothstep(0, 0.01, abs(distance)));
    if (desc.closerToVertex && iDisplayCloserToVertex)
    {
        col *= .7;
    }
    return float4(col, 1);
}
