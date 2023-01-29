add_falcor_executable(PolygonSDF)

target_sources(PolygonSDF PRIVATE
        Shaders/NaivePolygonDistance.3d.slang
        Shaders/SolidColor.3d.slang
        Shaders/UVColor.3d.slang

        Source/Editor/Aggregator/PolygonPeekingEditorAggregator.cpp
        Source/Editor/Aggregator/PolygonPeekingEditorAggregator.h

        Source/Editor/Command/AddPointStackCommand.cpp
        Source/Editor/Command/AddPointStackCommand.h
        Source/Editor/Command/SetPolygonStackCommand.cpp
        Source/Editor/Command/SetPolygonStackCommand.h
        Source/Editor/Command/StackCommand.h

        Source/Editor/Core/Editor.cpp
        Source/Editor/Core/Editor.h
        Source/Editor/Core/EditorAggregator.h
        Source/Editor/Core/EditorCommand.h
        Source/Editor/Core/EditorConstraint.h
        Source/Editor/Core/EditorConsumer.h
        Source/Editor/Core/EditorEvent.h
        Source/Editor/Core/EditorStack.cpp
        Source/Editor/Core/EditorStack.h
        Source/Editor/Core/EditorSupplier.h
        Source/Editor/Core/EditorSupplier.cpp
        Source/Editor/Core/EditorTransformation.h
        Source/Editor/Core/StackEntry.h

        Source/Editor/Event/ConstraintViolationEvent.cpp
        Source/Editor/Event/ConstraintViolationEvent.h
        Source/Editor/Event/NewStackCommandEvent.cpp
        Source/Editor/Event/NewStackCommandEvent.h
        Source/Editor/Event/StackTransformedEvent.cpp
        Source/Editor/Event/StackTransformedEvent.h
        Source/Editor/Event/UnknownCommandEvent.cpp
        Source/Editor/Event/UnknownCommandEvent.h

        Source/Editor/GuiInterface/GuiEditorEventConsumer.cpp
        Source/Editor/GuiInterface/GuiEditorEventConsumer.h
        Source/Editor/GuiInterface/GuiEditorInterface.cpp
        Source/Editor/GuiInterface/GuiEditorInterface.h

        Source/Editor/PolygonPresenter/PolygonPresenter.cpp
        Source/Editor/PolygonPresenter/PolygonPresenter.h

        Source/Polygon/Point.cpp
        Source/Polygon/Point.h
        Source/Polygon/Polygon.cpp
        Source/Polygon/Polygon.h
        Source/Polygon/Segment.cpp
        Source/Polygon/Segment.h

        Source/Rendering/FullScreenTriangle.cpp
        Source/Rendering/FullScreenTriangle.h
        Source/Rendering/RenderObject.h

        Source/Rendering/PolygonRenderer/Impl/AspectRatioIndependentPolygonRenderer.cpp
        Source/Rendering/PolygonRenderer/Impl/AspectRatioIndependentPolygonRenderer.h
        Source/Rendering/PolygonRenderer/Impl/CompositePolygonRenderer.cpp
        Source/Rendering/PolygonRenderer/Impl/CompositePolygonRenderer.h
        Source/Rendering/PolygonRenderer/Impl/FullScreenPolygonRenderer.cpp
        Source/Rendering/PolygonRenderer/Impl/FullScreenPolygonRenderer.h
        Source/Rendering/PolygonRenderer/Impl/PolygonOutlineRenderer.cpp
        Source/Rendering/PolygonRenderer/Impl/PolygonOutlineRenderer.h
        Source/Rendering/PolygonRenderer/Impl/ProxyPolygonRenderer.cpp
        Source/Rendering/PolygonRenderer/Impl/ProxyPolygonRenderer.h
        Source/Rendering/PolygonRenderer/PolygonRenderer.cpp
        Source/Rendering/PolygonRenderer/PolygonRenderer.h
        Source/Rendering/PolygonRenderer/PolygonRendererFactory.cpp
        Source/Rendering/PolygonRenderer/PolygonRendererFactory.h

        Source/Util/RangeGenerator.cpp
        Source/Util/RangeGenerator.h

        Source/Main.cpp
        Source/PolygonSDFApplication.cpp
        Source/PolygonSDFApplication.h
        )

target_copy_shaders(PolygonSDF PolygonSDF)

target_source_group(PolygonSDF Samples)
