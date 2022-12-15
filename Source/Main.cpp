#include "Falcor.h"
#include "PolygonSDF.h"

FALCOR_EXPORT_D3D12_AGILITY_SDK

int main(int argc, char **argv)
{
    psdf::PolygonSDF::UniquePtr pRenderer = std::make_unique<psdf::PolygonSDF>();

    SampleConfig config;
    config.windowDesc.title = "Polygon SDF";
    config.windowDesc.resizableWindow = true;
    config.windowDesc.width = 1280;
    config.windowDesc.height = 720;

    Sample::run(config, pRenderer);

    return 0;
}
