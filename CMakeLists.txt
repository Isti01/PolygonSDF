add_falcor_executable(PolygonSDF)

target_sources(PolygonSDF PRIVATE
        Shaders/NaivePolygonDistance.3d.slang
        Shaders/SolidColor.3d.slang
        Shaders/UVColor.3d.slang

        Source/Editor/Core/Editor.cpp
        Source/Editor/Core/Editor.h
        Source/Editor/Core/EditorAggregation.h
        Source/Editor/Core/EditorCommand.h
        Source/Editor/Core/EditorConstraint.h
        Source/Editor/Core/EditorConsumer.h
        Source/Editor/Core/EditorEvent.h
        Source/Editor/Core/EditorStack.h
        Source/Editor/Core/EditorSupplier.h
        Source/Editor/Core/EditorTransformation.h

        Source/Editor/Event/ConstraintViolationEvent.cpp
        Source/Editor/Event/ConstraintViolationEvent.h
        Source/Editor/Event/NewCommandEvent.cpp
        Source/Editor/Event/NewCommandEvent.h
        Source/Editor/Event/StackTransformedEvent.cpp
        Source/Editor/Event/StackTransformedEvent.h

        Source/Polygon/Point.cpp
        Source/Polygon/Point.h
        Source/Polygon/Polygon.cpp
        Source/Polygon/Polygon.h
        Source/Polygon/Segment.cpp
        Source/Polygon/Segment.h

        Source/Rendering/FullScreenTriangle.cpp
        Source/Rendering/FullScreenTriangle.h
        Source/Rendering/RenderObject.h

        Source/Rendering/PolygonRenderer/AspectRatioIndependentPolygonRenderer.cpp
        Source/Rendering/PolygonRenderer/AspectRatioIndependentPolygonRenderer.h
        Source/Rendering/PolygonRenderer/CompositePolygonRenderer.cpp
        Source/Rendering/PolygonRenderer/CompositePolygonRenderer.h
        Source/Rendering/PolygonRenderer/FullScreenPolygonRenderer.cpp
        Source/Rendering/PolygonRenderer/FullScreenPolygonRenderer.h
        Source/Rendering/PolygonRenderer/PolygonOutlineRenderer.cpp
        Source/Rendering/PolygonRenderer/PolygonOutlineRenderer.h
        Source/Rendering/PolygonRenderer/PolygonRenderer.cpp
        Source/Rendering/PolygonRenderer/PolygonRenderer.h
        Source/Rendering/PolygonRenderer/ProxyPolygonRenderer.cpp
        Source/Rendering/PolygonRenderer/ProxyPolygonRenderer.h

        Source/Util/RangeGenerator.cpp
        Source/Util/RangeGenerator.h

        Source/Main.cpp
        Source/PolygonSDFApplication.cpp
        Source/PolygonSDFApplication.h
        )

target_copy_shaders(PolygonSDF PolygonSDF)

target_source_group(PolygonSDF Samples)
