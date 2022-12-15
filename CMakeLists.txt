add_falcor_executable(PolygonSDF)

target_sources(PolygonSDF PRIVATE
        Shaders/SolidColor.slang
        Shaders/UVColor.slang

        Source/Polygon/Point.cpp
        Source/Polygon/Point.h
        Source/Polygon/Polygon.cpp
        Source/Polygon/Polygon.h
        Source/Polygon/Segment.cpp
        Source/Polygon/Segment.h

        Source/Rendering/FullScreenTriangle.cpp
        Source/Rendering/FullScreenTriangle.h
        Source/Rendering/RenderObject.h

        Source/Rendering/PolygonRenderer/PolygonOutlineRenderer.cpp
        Source/Rendering/PolygonRenderer/PolygonOutlineRenderer.h
        Source/Rendering/PolygonRenderer/PolygonRenderer.cpp
        Source/Rendering/PolygonRenderer/PolygonRenderer.h

        Source/Util/RangeGenerator.cpp
        Source/Util/RangeGenerator.h

        Source/Main.cpp
        Source/PolygonSDF.cpp
        Source/PolygonSDF.h
        )

target_copy_shaders(PolygonSDF PolygonSDF)

target_source_group(PolygonSDF Samples)
