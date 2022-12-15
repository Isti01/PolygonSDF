add_falcor_executable(PolygonSDF)

target_sources(PolygonSDF PRIVATE
        Shaders/PolygonSDF.slang

        Source/DistancePass/DistancePass.cpp
        Source/DistancePass/DistancePass.h
        Source/DistancePass/FullScreenTriangle.cpp
        Source/DistancePass/FullScreenTriangle.h

        Source/Polygon/Point.cpp
        Source/Polygon/Point.h
        Source/Polygon/Polygon.cpp
        Source/Polygon/Polygon.h
        Source/Polygon/Segment.cpp
        Source/Polygon/Segment.h

        Source/PolygonRenderer/PolygonOutlineRenderer.cpp
        Source/PolygonRenderer/PolygonOutlineRenderer.h

        Source/Rendering/RenderObject.h

        Source/Main.cpp
        Source/PolygonSDF.cpp
        Source/PolygonSDF.h
        )

target_copy_shaders(PolygonSDF PolygonSDF)

target_source_group(PolygonSDF Samples)
