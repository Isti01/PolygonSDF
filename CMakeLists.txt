add_falcor_executable(PolygonSDF)

target_sources(PolygonSDF PRIVATE
        Shaders/NaivePolygonDistance.3d.slang
        Shaders/SolidColor.3d.slang

        Source/Algorithm/Region/LineRegion.cpp
        Source/Algorithm/Region/LineRegion.h
        Source/Algorithm/Region/PointRegion.cpp
        Source/Algorithm/Region/PointRegion.h
        Source/Algorithm/Region/Region.cpp
        Source/Algorithm/Region/Region.h

        Source/Algorithm/SdfPlaneAlgorithm.cpp
        Source/Algorithm/SdfPlaneAlgorithm.h

        Source/Editor/Aggregator/StackPeekingEditorAggregator.cpp
        Source/Editor/Aggregator/StackPeekingEditorAggregator.h
        Source/Editor/Aggregator/StackSizeEditorAggregator.cpp
        Source/Editor/Aggregator/StackSizeEditorAggregator.h

        Source/Editor/Command/AddPointStackCommand.cpp
        Source/Editor/Command/AddPointStackCommand.h
        Source/Editor/Command/DeletePointStackCommand.cpp
        Source/Editor/Command/DeletePointStackCommand.h
        Source/Editor/Command/InsertPointStackCommand.cpp
        Source/Editor/Command/InsertPointStackCommand.h
        Source/Editor/Command/SetPolygonStackCommand.cpp
        Source/Editor/Command/SetPolygonStackCommand.h
        Source/Editor/Command/StackCommand.cpp
        Source/Editor/Command/StackCommand.h
        Source/Editor/Command/UpdatePointStackCommand.cpp
        Source/Editor/Command/UpdatePointStackCommand.h

        Source/Editor/Core/Editor.cpp
        Source/Editor/Core/Editor.h
        Source/Editor/Core/EditorAggregator.h
        Source/Editor/Core/EditorCommand.h
        Source/Editor/Core/EditorConstraint.h
        Source/Editor/Core/EditorConsumer.h
        Source/Editor/Core/EditorEvent.h
        Source/Editor/Core/EditorStack.cpp
        Source/Editor/Core/EditorStack.h
        Source/Editor/Core/EditorTransformation.h
        Source/Editor/Core/StackEntry.cpp
        Source/Editor/Core/StackEntry.h

        Source/Editor/Event/Menu/EventMenu.cpp
        Source/Editor/Event/Menu/EventMenu.h
        Source/Editor/Event/Menu/EventMenuGui.cpp
        Source/Editor/Event/Menu/EventMenuGui.h
        Source/Editor/Event/Menu/EventMenuEditorConsumer.cpp
        Source/Editor/Event/Menu/EventMenuEditorConsumer.h

        Source/Editor/Event/ConstraintViolationEvent.cpp
        Source/Editor/Event/ConstraintViolationEvent.h
        Source/Editor/Event/NewStackCommandEvent.cpp
        Source/Editor/Event/NewStackCommandEvent.h
        Source/Editor/Event/StackTransformedEvent.cpp
        Source/Editor/Event/StackTransformedEvent.h
        Source/Editor/Event/UnknownCommandEvent.cpp
        Source/Editor/Event/UnknownCommandEvent.h

        Source/Editor/GuiEditor/GuiEditor.cpp
        Source/Editor/GuiEditor/GuiEditor.h

        Source/Editor/Transformation/ClearHistoryEditorTransformation.cpp
        Source/Editor/Transformation/ClearHistoryEditorTransformation.h
        Source/Editor/Transformation/UndoEditorTransformation.cpp
        Source/Editor/Transformation/UndoEditorTransformation.h

        Source/Editor/VisualEditor/Input/DragMouseInputHandler.cpp
        Source/Editor/VisualEditor/Input/DragMouseInputHandler.h
        Source/Editor/VisualEditor/Input/InsertRemoveVertexInputHandler.cpp
        Source/Editor/VisualEditor/Input/InsertRemoveVertexInputHandler.h
        Source/Editor/VisualEditor/Input/MouseInputHandler.h
        Source/Editor/VisualEditor/Input/VertexMoveInputHandler.cpp
        Source/Editor/VisualEditor/Input/VertexMoveInputHandler.h

        Source/Editor/VisualEditor/PolygonPresenter/PolygonPresenter.cpp
        Source/Editor/VisualEditor/PolygonPresenter/PolygonPresenter.h

        Source/Editor/VisualEditor/VisualEditor.cpp
        Source/Editor/VisualEditor/VisualEditor.h
        Source/Editor/VisualEditor/VisualEditorConstants.h

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

        Source/Util/CoordinateUtil.cpp
        Source/Util/CoordinateUtil.h
        Source/Util/Deferred.h
        Source/Util/IndexUtil.cpp
        Source/Util/IndexUtil.h
        Source/Util/RangeGenerator.cpp
        Source/Util/RangeGenerator.h
        Source/Util/WithImGuiId.cpp
        Source/Util/WithImGuiId.h

        Source/Main.cpp
        Source/PolygonSDFApplication.cpp
        Source/PolygonSDFApplication.h
        )

target_copy_shaders(PolygonSDF PolygonSDF)
target_copy_data_folder(PolygonSDF)

target_source_group(PolygonSDF Samples)


#### A separate executable for testing
add_falcor_executable(PolygonSDFTest)

target_sources(PolygonSDFTest PRIVATE
        Shaders/NaivePolygonDistance.3d.slang
        Shaders/SolidColor.3d.slang

        Source/Algorithm/Region/LineRegion.cpp
        Source/Algorithm/Region/LineRegion.h
        Source/Algorithm/Region/PointRegion.cpp
        Source/Algorithm/Region/PointRegion.h
        Source/Algorithm/Region/Region.cpp
        Source/Algorithm/Region/Region.h

        Source/Algorithm/SdfPlaneAlgorithm.cpp
        Source/Algorithm/SdfPlaneAlgorithm.h

        Source/Editor/Aggregator/StackPeekingEditorAggregator.cpp
        Source/Editor/Aggregator/StackPeekingEditorAggregator.h
        Source/Editor/Aggregator/StackSizeEditorAggregator.cpp
        Source/Editor/Aggregator/StackSizeEditorAggregator.h

        Source/Editor/Command/AddPointStackCommand.cpp
        Source/Editor/Command/AddPointStackCommand.h
        Source/Editor/Command/DeletePointStackCommand.cpp
        Source/Editor/Command/DeletePointStackCommand.h
        Source/Editor/Command/InsertPointStackCommand.cpp
        Source/Editor/Command/InsertPointStackCommand.h
        Source/Editor/Command/SetPolygonStackCommand.cpp
        Source/Editor/Command/SetPolygonStackCommand.h
        Source/Editor/Command/StackCommand.cpp
        Source/Editor/Command/StackCommand.h
        Source/Editor/Command/UpdatePointStackCommand.cpp
        Source/Editor/Command/UpdatePointStackCommand.h

        Source/Editor/Core/Editor.cpp
        Source/Editor/Core/Editor.h
        Source/Editor/Core/EditorAggregator.h
        Source/Editor/Core/EditorCommand.h
        Source/Editor/Core/EditorConstraint.h
        Source/Editor/Core/EditorConsumer.h
        Source/Editor/Core/EditorEvent.h
        Source/Editor/Core/EditorStack.cpp
        Source/Editor/Core/EditorStack.h
        Source/Editor/Core/EditorTransformation.h
        Source/Editor/Core/StackEntry.cpp
        Source/Editor/Core/StackEntry.h

        Source/Editor/Event/Menu/EventMenu.cpp
        Source/Editor/Event/Menu/EventMenu.h
        Source/Editor/Event/Menu/EventMenuGui.cpp
        Source/Editor/Event/Menu/EventMenuGui.h
        Source/Editor/Event/Menu/EventMenuEditorConsumer.cpp
        Source/Editor/Event/Menu/EventMenuEditorConsumer.h

        Source/Editor/Event/ConstraintViolationEvent.cpp
        Source/Editor/Event/ConstraintViolationEvent.h
        Source/Editor/Event/NewStackCommandEvent.cpp
        Source/Editor/Event/NewStackCommandEvent.h
        Source/Editor/Event/StackTransformedEvent.cpp
        Source/Editor/Event/StackTransformedEvent.h
        Source/Editor/Event/UnknownCommandEvent.cpp
        Source/Editor/Event/UnknownCommandEvent.h

        Source/Editor/GuiEditor/GuiEditor.cpp
        Source/Editor/GuiEditor/GuiEditor.h

        Source/Editor/Transformation/ClearHistoryEditorTransformation.cpp
        Source/Editor/Transformation/ClearHistoryEditorTransformation.h
        Source/Editor/Transformation/UndoEditorTransformation.cpp
        Source/Editor/Transformation/UndoEditorTransformation.h

        Source/Editor/VisualEditor/Input/DragMouseInputHandler.cpp
        Source/Editor/VisualEditor/Input/DragMouseInputHandler.h
        Source/Editor/VisualEditor/Input/InsertRemoveVertexInputHandler.cpp
        Source/Editor/VisualEditor/Input/InsertRemoveVertexInputHandler.h
        Source/Editor/VisualEditor/Input/MouseInputHandler.h
        Source/Editor/VisualEditor/Input/VertexMoveInputHandler.cpp
        Source/Editor/VisualEditor/Input/VertexMoveInputHandler.h

        Source/Editor/VisualEditor/PolygonPresenter/PolygonPresenter.cpp
        Source/Editor/VisualEditor/PolygonPresenter/PolygonPresenter.h

        Source/Editor/VisualEditor/VisualEditor.cpp
        Source/Editor/VisualEditor/VisualEditor.h
        Source/Editor/VisualEditor/VisualEditorConstants.h

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

        Source/Util/CoordinateUtil.cpp
        Source/Util/CoordinateUtil.h
        Source/Util/Deferred.h
        Source/Util/IndexUtil.cpp
        Source/Util/IndexUtil.h
        Source/Util/RangeGenerator.cpp
        Source/Util/RangeGenerator.h
        Source/Util/WithImGuiId.cpp
        Source/Util/WithImGuiId.h

        Source/PolygonSDFApplication.cpp
        Source/PolygonSDFApplication.h

        Tests/Algorithm/Region/TestPointRegionCutWithPoints.h
        Tests/Algorithm/Region/TestPolyCut.h

        Tests/External/catch.hpp

        Tests/Util/TestUtils.cpp
        Tests/Util/TestUtils.h

        Tests/Main.cpp
        )

target_copy_shaders(PolygonSDFTest PolygonSDF)
target_copy_data_folder(PolygonSDFTest)

target_source_group(PolygonSDFTest Samples)
