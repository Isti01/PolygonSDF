add_falcor_executable(PolygonSDF)

target_sources(PolygonSDF PRIVATE
        Shaders/Common.slang
        Shaders/LineRegionAlgorithmOutput.3d.slang
        Shaders/NaivePolygonDistance.3d.slang
        Shaders/PointRegionAlgorithmOutput.3d.slang
        Shaders/SolidColor.3d.slang

        Source/Algorithm/Region/LineRegion.cpp
        Source/Algorithm/Region/LineRegion.h
        Source/Algorithm/Region/PointRegion.cpp
        Source/Algorithm/Region/PointRegion.h
        Source/Algorithm/Region/Region.cpp
        Source/Algorithm/Region/Region.h
        Source/Algorithm/Region/LineRegionBoundVertex.h

        Source/Algorithm/SdfPlaneAlgorithm.cpp
        Source/Algorithm/SdfPlaneAlgorithm.h
        Source/Algorithm/SdfPlaneAlgorithmOutput.cpp
        Source/Algorithm/SdfPlaneAlgorithmOutput.h

        Source/Editor/Aggregator/StackPeekingEditorAggregator.cpp
        Source/Editor/Aggregator/StackPeekingEditorAggregator.h
        Source/Editor/Aggregator/StackSizeEditorAggregator.cpp
        Source/Editor/Aggregator/StackSizeEditorAggregator.h

        Source/Editor/Command/AddNewGroupStackCommand.cpp
        Source/Editor/Command/AddNewGroupStackCommand.h
        Source/Editor/Command/AddPointStackCommand.cpp
        Source/Editor/Command/AddPointStackCommand.h
        Source/Editor/Command/CalculateSdfPlaneAlgorithmCommand.cpp
        Source/Editor/Command/CalculateSdfPlaneAlgorithmCommand.h
        Source/Editor/Command/DeleteGroupStackCommand.cpp
        Source/Editor/Command/DeleteGroupStackCommand.h
        Source/Editor/Command/DeletePointStackCommand.cpp
        Source/Editor/Command/DeletePointStackCommand.h
        Source/Editor/Command/InsertPointStackCommand.cpp
        Source/Editor/Command/InsertPointStackCommand.h
        Source/Editor/Command/MergePolygonWithOffsetStackCommand.cpp
        Source/Editor/Command/MergePolygonWithOffsetStackCommand.h
        Source/Editor/Command/MoveGroupStackCommand.cpp
        Source/Editor/Command/MoveGroupStackCommand.h
        Source/Editor/Command/SetPolygonStackCommand.cpp
        Source/Editor/Command/SetPolygonStackCommand.h
        Source/Editor/Command/StackCommand.cpp
        Source/Editor/Command/StackCommand.h
        Source/Editor/Command/UpdatePointStackCommand.cpp
        Source/Editor/Command/UpdatePointStackCommand.h

        Source/Editor/Constraint/DeleteGroupEditorConstraint.cpp
        Source/Editor/Constraint/DeleteGroupEditorConstraint.h
        Source/Editor/Constraint/DeletePointEditorConstraint.cpp
        Source/Editor/Constraint/DeletePointEditorConstraint.h
        Source/Editor/Constraint/SdfPlaneAlgorithmConstraint.cpp
        Source/Editor/Constraint/SdfPlaneAlgorithmConstraint.h

        Source/Editor/Consumer/EventMenuEditorConsumer.cpp
        Source/Editor/Consumer/EventMenuEditorConsumer.h
        Source/Editor/Consumer/GuiStateEditorConsumer.cpp
        Source/Editor/Consumer/GuiStateEditorConsumer.h

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
        Source/Editor/Core/PublishedEvent.cpp
        Source/Editor/Core/PublishedEvent.h
        Source/Editor/Core/StackEntry.cpp
        Source/Editor/Core/StackEntry.h

        Source/Editor/Event/Menu/EventMenu.cpp
        Source/Editor/Event/Menu/EventMenu.h
        Source/Editor/Event/Menu/EventMenuGui.cpp
        Source/Editor/Event/Menu/EventMenuGui.h

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

        Source/Editor/PublishedEvent/HideGuiPublishedEvent.cpp
        Source/Editor/PublishedEvent/HideGuiPublishedEvent.h
        Source/Editor/PublishedEvent/ShowGuiPublishedEvent.cpp
        Source/Editor/PublishedEvent/ShowGuiPublishedEvent.h

        Source/Editor/Transformation/ClearHistoryEditorTransformation.cpp
        Source/Editor/Transformation/ClearHistoryEditorTransformation.h
        Source/Editor/Transformation/UndoEditorTransformation.cpp
        Source/Editor/Transformation/UndoEditorTransformation.h

        Source/Editor/VisualEditor/Input/DragMouseInputHandler.cpp
        Source/Editor/VisualEditor/Input/DragMouseInputHandler.h
        Source/Editor/VisualEditor/Input/InsertRemoveVertexInputHandler.cpp
        Source/Editor/VisualEditor/Input/InsertRemoveVertexInputHandler.h
        Source/Editor/VisualEditor/Input/MouseInputHandler.h
        Source/Editor/VisualEditor/Input/MoveInputHandler.cpp
        Source/Editor/VisualEditor/Input/MoveInputHandler.h

        Source/Editor/VisualEditor/Presenter/PolygonPresenter.cpp
        Source/Editor/VisualEditor/Presenter/PolygonPresenter.h
        Source/Editor/VisualEditor/Presenter/Presenter.h
        Source/Editor/VisualEditor/Presenter/SdfAlgorithmOutputPresenter.cpp
        Source/Editor/VisualEditor/Presenter/SdfAlgorithmOutputPresenter.h

        Source/Editor/VisualEditor/VisualEditor.cpp
        Source/Editor/VisualEditor/VisualEditor.h
        Source/Editor/VisualEditor/VisualEditorConstants.h

        Source/Polygon/Point.h
        Source/Polygon/Polygon.cpp
        Source/Polygon/Polygon.h
        Source/Polygon/Segment.cpp
        Source/Polygon/Segment.h
        Source/Polygon/SubPolygon.cpp
        Source/Polygon/SubPolygon.h

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
        Source/Rendering/PolygonRenderer/Impl/SdfAlgorithmLineRegionRenderer.cpp
        Source/Rendering/PolygonRenderer/Impl/SdfAlgorithmLineRegionRenderer.h
        Source/Rendering/PolygonRenderer/Impl/SdfAlgorithmOutputRenderer.cpp
        Source/Rendering/PolygonRenderer/Impl/SdfAlgorithmOutputRenderer.h
        Source/Rendering/PolygonRenderer/Impl/SdfAlgorithmPointRegionRenderer.cpp
        Source/Rendering/PolygonRenderer/Impl/SdfAlgorithmPointRegionRenderer.h

        Source/Util/CoordinateUtil.cpp
        Source/Util/CoordinateUtil.h
        Source/Util/Deferred.h
        Source/Util/IndexUtil.cpp
        Source/Util/IndexUtil.h
        Source/Util/MathUtil.h
        Source/Util/RangeGenerator.cpp
        Source/Util/RangeGenerator.h
        Source/Util/WithImGuiId.cpp
        Source/Util/WithImGuiId.h

        Source/CommonConstants.h
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
        Shaders/Common.slang
        Shaders/LineRegionAlgorithmOutput.3d.slang
        Shaders/NaivePolygonDistance.3d.slang
        Shaders/PointRegionAlgorithmOutput.3d.slang
        Shaders/SolidColor.3d.slang

        Source/Algorithm/Region/LineRegion.cpp
        Source/Algorithm/Region/LineRegion.h
        Source/Algorithm/Region/PointRegion.cpp
        Source/Algorithm/Region/PointRegion.h
        Source/Algorithm/Region/Region.cpp
        Source/Algorithm/Region/Region.h
        Source/Algorithm/Region/LineRegionBoundVertex.h

        Source/Algorithm/SdfPlaneAlgorithm.cpp
        Source/Algorithm/SdfPlaneAlgorithm.h
        Source/Algorithm/SdfPlaneAlgorithmOutput.cpp
        Source/Algorithm/SdfPlaneAlgorithmOutput.h

        Source/Editor/Aggregator/StackPeekingEditorAggregator.cpp
        Source/Editor/Aggregator/StackPeekingEditorAggregator.h
        Source/Editor/Aggregator/StackSizeEditorAggregator.cpp
        Source/Editor/Aggregator/StackSizeEditorAggregator.h

        Source/Editor/Command/AddNewGroupStackCommand.cpp
        Source/Editor/Command/AddNewGroupStackCommand.h
        Source/Editor/Command/AddPointStackCommand.cpp
        Source/Editor/Command/AddPointStackCommand.h
        Source/Editor/Command/CalculateSdfPlaneAlgorithmCommand.cpp
        Source/Editor/Command/CalculateSdfPlaneAlgorithmCommand.h
        Source/Editor/Command/DeleteGroupStackCommand.cpp
        Source/Editor/Command/DeleteGroupStackCommand.h
        Source/Editor/Command/DeletePointStackCommand.cpp
        Source/Editor/Command/DeletePointStackCommand.h
        Source/Editor/Command/InsertPointStackCommand.cpp
        Source/Editor/Command/InsertPointStackCommand.h
        Source/Editor/Command/MergePolygonWithOffsetStackCommand.cpp
        Source/Editor/Command/MergePolygonWithOffsetStackCommand.h
        Source/Editor/Command/MoveGroupStackCommand.cpp
        Source/Editor/Command/MoveGroupStackCommand.h
        Source/Editor/Command/SetPolygonStackCommand.cpp
        Source/Editor/Command/SetPolygonStackCommand.h
        Source/Editor/Command/StackCommand.cpp
        Source/Editor/Command/StackCommand.h
        Source/Editor/Command/UpdatePointStackCommand.cpp
        Source/Editor/Command/UpdatePointStackCommand.h

        Source/Editor/Constraint/DeleteGroupEditorConstraint.cpp
        Source/Editor/Constraint/DeleteGroupEditorConstraint.h
        Source/Editor/Constraint/DeletePointEditorConstraint.cpp
        Source/Editor/Constraint/DeletePointEditorConstraint.h
        Source/Editor/Constraint/SdfPlaneAlgorithmConstraint.cpp
        Source/Editor/Constraint/SdfPlaneAlgorithmConstraint.h

        Source/Editor/Consumer/EventMenuEditorConsumer.cpp
        Source/Editor/Consumer/EventMenuEditorConsumer.h
        Source/Editor/Consumer/GuiStateEditorConsumer.cpp
        Source/Editor/Consumer/GuiStateEditorConsumer.h

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
        Source/Editor/Core/PublishedEvent.cpp
        Source/Editor/Core/PublishedEvent.h
        Source/Editor/Core/StackEntry.cpp
        Source/Editor/Core/StackEntry.h

        Source/Editor/Event/Menu/EventMenu.cpp
        Source/Editor/Event/Menu/EventMenu.h
        Source/Editor/Event/Menu/EventMenuGui.cpp
        Source/Editor/Event/Menu/EventMenuGui.h

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

        Source/Editor/PublishedEvent/HideGuiPublishedEvent.cpp
        Source/Editor/PublishedEvent/HideGuiPublishedEvent.h
        Source/Editor/PublishedEvent/ShowGuiPublishedEvent.cpp
        Source/Editor/PublishedEvent/ShowGuiPublishedEvent.h

        Source/Editor/Transformation/ClearHistoryEditorTransformation.cpp
        Source/Editor/Transformation/ClearHistoryEditorTransformation.h
        Source/Editor/Transformation/UndoEditorTransformation.cpp
        Source/Editor/Transformation/UndoEditorTransformation.h

        Source/Editor/VisualEditor/Input/DragMouseInputHandler.cpp
        Source/Editor/VisualEditor/Input/DragMouseInputHandler.h
        Source/Editor/VisualEditor/Input/InsertRemoveVertexInputHandler.cpp
        Source/Editor/VisualEditor/Input/InsertRemoveVertexInputHandler.h
        Source/Editor/VisualEditor/Input/MouseInputHandler.h
        Source/Editor/VisualEditor/Input/MoveInputHandler.cpp
        Source/Editor/VisualEditor/Input/MoveInputHandler.h

        Source/Editor/VisualEditor/Presenter/PolygonPresenter.cpp
        Source/Editor/VisualEditor/Presenter/PolygonPresenter.h
        Source/Editor/VisualEditor/Presenter/Presenter.h
        Source/Editor/VisualEditor/Presenter/SdfAlgorithmOutputPresenter.cpp
        Source/Editor/VisualEditor/Presenter/SdfAlgorithmOutputPresenter.h

        Source/Editor/VisualEditor/VisualEditor.cpp
        Source/Editor/VisualEditor/VisualEditor.h
        Source/Editor/VisualEditor/VisualEditorConstants.h

        Source/Polygon/Point.h
        Source/Polygon/Polygon.cpp
        Source/Polygon/Polygon.h
        Source/Polygon/Segment.cpp
        Source/Polygon/Segment.h
        Source/Polygon/SubPolygon.cpp
        Source/Polygon/SubPolygon.h

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
        Source/Rendering/PolygonRenderer/Impl/SdfAlgorithmLineRegionRenderer.cpp
        Source/Rendering/PolygonRenderer/Impl/SdfAlgorithmLineRegionRenderer.h
        Source/Rendering/PolygonRenderer/Impl/SdfAlgorithmOutputRenderer.cpp
        Source/Rendering/PolygonRenderer/Impl/SdfAlgorithmOutputRenderer.h
        Source/Rendering/PolygonRenderer/Impl/SdfAlgorithmPointRegionRenderer.cpp
        Source/Rendering/PolygonRenderer/Impl/SdfAlgorithmPointRegionRenderer.h

        Source/Util/CoordinateUtil.cpp
        Source/Util/CoordinateUtil.h
        Source/Util/Deferred.h
        Source/Util/IndexUtil.cpp
        Source/Util/IndexUtil.h
        Source/Util/MathUtil.h
        Source/Util/RangeGenerator.cpp
        Source/Util/RangeGenerator.h
        Source/Util/WithImGuiId.cpp
        Source/Util/WithImGuiId.h

        Source/CommonConstants.h
        Source/PolygonSDFApplication.cpp
        Source/PolygonSDFApplication.h

        Tests/Algorithm/Region/TestLineRegionCutWithLines.h
        Tests/Algorithm/Region/TestLineRegionCutWithPoints.h
        Tests/Algorithm/Region/TestPointRegionCutWithLines.h
        Tests/Algorithm/Region/TestPointRegionCutWithPoints.h
        Tests/Algorithm/Region/TestPolyCut.h

        Tests/Algorithm/TestSdfPlaneAlgorithm.h

        Tests/External/catch.hpp

        Tests/Util/TestUtils.cpp
        Tests/Util/TestUtils.h

        Tests/Main.cpp
        )

target_copy_shaders(PolygonSDFTest PolygonSDF)
target_copy_data_folder(PolygonSDFTest)

target_source_group(PolygonSDFTest Samples)
