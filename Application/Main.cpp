#include "PolygonSDFApplication.h"
#include <Falcor.h>

FALCOR_EXPORT_D3D12_AGILITY_SDK

using namespace Falcor;

int main(int argc, char **argv)
{
    psdf::PolygonSDFApplication::UniquePtr pRenderer = std::make_unique<psdf::PolygonSDFApplication>();

    SampleConfig config;
    config.windowDesc.title = "Polygon SDF";
    config.windowDesc.resizableWindow = true;
    config.windowDesc.width = 1280;
    config.windowDesc.height = 720;
    config.deviceDesc.enableVsync = true;

    Sample::run(config, pRenderer);

    return 0;
}
