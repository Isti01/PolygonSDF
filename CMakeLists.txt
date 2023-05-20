add_library(PolygonSDF
        Shaders/DistanceVisualization.slang
        Shaders/EdgeRegionAlgorithmOutput.3d.slang
        Shaders/NaivePolygonDistance.3d.slang
        Shaders/SolidColor.3d.slang
        Shaders/VertexRegionAlgorithmOutput.3d.slang

        Source/Algorithm/Region/EdgeRegion.cpp
        Source/Algorithm/Region/EdgeRegion.h
        Source/Algorithm/Region/EdgeRegionBoundVertex.h
        Source/Algorithm/Region/Region.cpp
        Source/Algorithm/Region/Region.h
        Source/Algorithm/Region/VertexRegion.cpp
        Source/Algorithm/Region/VertexRegion.h
        Source/Algorithm/Region/VertexRegionBoundVertex.h

        Source/Algorithm/SdfPlaneAlgorithm.cpp
        Source/Algorithm/SdfPlaneAlgorithm.h
        Source/Algorithm/SdfPlaneAlgorithmExecutionDesc.h
        Source/Algorithm/SdfPlaneAlgorithmOutput.cpp
        Source/Algorithm/SdfPlaneAlgorithmOutput.h

        Source/Editor/Aggregator/StackPeekingEditorAggregator.cpp
        Source/Editor/Aggregator/StackPeekingEditorAggregator.h
        Source/Editor/Aggregator/StackSizeEditorAggregator.cpp
        Source/Editor/Aggregator/StackSizeEditorAggregator.h

        Source/Editor/Command/AddNewOutlineStackCommand.cpp
        Source/Editor/Command/AddNewOutlineStackCommand.h
        Source/Editor/Command/AddVertexStackCommand.cpp
        Source/Editor/Command/AddVertexStackCommand.h
        Source/Editor/Command/CalculateSdfPlaneAlgorithmCommand.cpp
        Source/Editor/Command/CalculateSdfPlaneAlgorithmCommand.h
        Source/Editor/Command/DeleteOutlineStackCommand.cpp
        Source/Editor/Command/DeleteOutlineStackCommand.h
        Source/Editor/Command/DeleteVertexStackCommand.cpp
        Source/Editor/Command/DeleteVertexStackCommand.h
        Source/Editor/Command/InsertVertexStackCommand.cpp
        Source/Editor/Command/InsertVertexStackCommand.h
        Source/Editor/Command/MergeShapeWithOffsetStackCommand.cpp
        Source/Editor/Command/MergeShapeWithOffsetStackCommand.h
        Source/Editor/Command/MoveOutlineStackCommand.cpp
        Source/Editor/Command/MoveOutlineStackCommand.h
        Source/Editor/Command/SetShapeStackCommand.cpp
        Source/Editor/Command/SetShapeStackCommand.h
        Source/Editor/Command/StackCommand.cpp
        Source/Editor/Command/StackCommand.h
        Source/Editor/Command/UpdateVertexStackCommand.cpp
        Source/Editor/Command/UpdateVertexStackCommand.h

        Source/Editor/Constraint/DeleteOutlineEditorConstraint.cpp
        Source/Editor/Constraint/DeleteOutlineEditorConstraint.h
        Source/Editor/Constraint/DeleteVertexEditorConstraint.cpp
        Source/Editor/Constraint/DeleteVertexEditorConstraint.h
        Source/Editor/Constraint/SdfPlaneAlgorithmConstraint.cpp
        Source/Editor/Constraint/SdfPlaneAlgorithmConstraint.h

        Source/Editor/Consumer/EventMenuEditorConsumer.cpp
        Source/Editor/Consumer/EventMenuEditorConsumer.h
        Source/Editor/Consumer/GuiStateEditorConsumer.cpp
        Source/Editor/Consumer/GuiStateEditorConsumer.h
        Source/Editor/Consumer/PropertyUpdatingEditorConsumer.cpp
        Source/Editor/Consumer/PropertyUpdatingEditorConsumer.h
        Source/Editor/Consumer/VisualEditorStateChangeEditorConsumer.cpp
        Source/Editor/Consumer/VisualEditorStateChangeEditorConsumer.h

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

        Source/Editor/Event/ConstraintViolationEvent.cpp
        Source/Editor/Event/ConstraintViolationEvent.h
        Source/Editor/Event/NewStackCommandEvent.cpp
        Source/Editor/Event/NewStackCommandEvent.h
        Source/Editor/Event/StackTransformedEvent.cpp
        Source/Editor/Event/StackTransformedEvent.h
        Source/Editor/Event/UnknownCommandEvent.cpp
        Source/Editor/Event/UnknownCommandEvent.h

        Source/Editor/GuiEditor/EditorGuideMenu.cpp
        Source/Editor/GuiEditor/EditorGuideMenu.h
        Source/Editor/GuiEditor/EventMenu.cpp
        Source/Editor/GuiEditor/EventMenu.h
        Source/Editor/GuiEditor/EventMenuGui.cpp
        Source/Editor/GuiEditor/EventMenuGui.h
        Source/Editor/GuiEditor/GuiEditor.cpp
        Source/Editor/GuiEditor/GuiEditor.h
        Source/Editor/GuiEditor/GuiEditorActionsMenu.cpp
        Source/Editor/GuiEditor/GuiEditorActionsMenu.h
        Source/Editor/GuiEditor/GuiEditorMenu.h
        Source/Editor/GuiEditor/GuiShapeActionsMenu.cpp
        Source/Editor/GuiEditor/GuiShapeActionsMenu.h
        Source/Editor/GuiEditor/GuiVisualizationSettingsMenu.cpp
        Source/Editor/GuiEditor/GuiVisualizationSettingsMenu.h

        Source/Editor/PublishedEvent/HideGuiPublishedEvent.cpp
        Source/Editor/PublishedEvent/HideGuiPublishedEvent.h
        Source/Editor/PublishedEvent/RendererPropertyPublishedEvent.cpp
        Source/Editor/PublishedEvent/RendererPropertyPublishedEvent.h
        Source/Editor/PublishedEvent/ShowGuiPublishedEvent.cpp
        Source/Editor/PublishedEvent/ShowGuiPublishedEvent.h
        Source/Editor/PublishedEvent/VisualEditorModeChangedPublishedEvent.cpp
        Source/Editor/PublishedEvent/VisualEditorModeChangedPublishedEvent.h

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

        Source/Editor/VisualEditor/Presenter/Presenter.cpp
        Source/Editor/VisualEditor/Presenter/Presenter.h
        Source/Editor/VisualEditor/Presenter/SdfAlgorithmOutputPresenter.cpp
        Source/Editor/VisualEditor/Presenter/SdfAlgorithmOutputPresenter.h
        Source/Editor/VisualEditor/Presenter/ShapePresenter.cpp
        Source/Editor/VisualEditor/Presenter/ShapePresenter.h

        Source/Editor/VisualEditor/VisualEditor.cpp
        Source/Editor/VisualEditor/VisualEditor.h
        Source/Editor/VisualEditor/VisualEditorConstants.h

        Source/Shape/Edge.cpp
        Source/Shape/Edge.h
        Source/Shape/Outline.cpp
        Source/Shape/Outline.h
        Source/Shape/Shape.cpp
        Source/Shape/Shape.h
        Source/Shape/Vertex.h

        Source/Rendering/ShapeRenderer/Impl/AspectRatioIndependentShapeRenderer.cpp
        Source/Rendering/ShapeRenderer/Impl/AspectRatioIndependentShapeRenderer.h
        Source/Rendering/ShapeRenderer/Impl/CompositeShapeRenderer.cpp
        Source/Rendering/ShapeRenderer/Impl/CompositeShapeRenderer.h
        Source/Rendering/ShapeRenderer/Impl/EmptyShapeRenderer.cpp
        Source/Rendering/ShapeRenderer/Impl/EmptyShapeRenderer.h
        Source/Rendering/ShapeRenderer/Impl/FullScreenShapeRenderer.cpp
        Source/Rendering/ShapeRenderer/Impl/FullScreenShapeRenderer.h
        Source/Rendering/ShapeRenderer/Impl/ProxyShapeRenderer.cpp
        Source/Rendering/ShapeRenderer/Impl/ProxyShapeRenderer.h
        Source/Rendering/ShapeRenderer/Impl/SdfAlgorithmEdgeRegionRenderer.cpp
        Source/Rendering/ShapeRenderer/Impl/SdfAlgorithmEdgeRegionRenderer.h
        Source/Rendering/ShapeRenderer/Impl/SdfAlgorithmOutputRenderer.cpp
        Source/Rendering/ShapeRenderer/Impl/SdfAlgorithmOutputRenderer.h
        Source/Rendering/ShapeRenderer/Impl/SdfAlgorithmVertexRegionRenderer.cpp
        Source/Rendering/ShapeRenderer/Impl/SdfAlgorithmVertexRegionRenderer.h
        Source/Rendering/ShapeRenderer/Impl/ShapeOutlineRenderer.cpp
        Source/Rendering/ShapeRenderer/Impl/ShapeOutlineRenderer.h

        Source/Rendering/ShapeRenderer/RendererProperties.cpp
        Source/Rendering/ShapeRenderer/RendererProperties.h
        Source/Rendering/ShapeRenderer/ShapeRenderer.cpp
        Source/Rendering/ShapeRenderer/ShapeRenderer.h
        Source/Rendering/ShapeRenderer/ShapeRendererFactory.cpp
        Source/Rendering/ShapeRenderer/ShapeRendererFactory.h
        Source/Rendering/ShapeRenderer/ShapeRendererProperty.h

        Source/Rendering/FullScreenTriangle.cpp
        Source/Rendering/FullScreenTriangle.h
        Source/Rendering/RenderObject.h

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
        )

target_link_libraries(PolygonSDF PRIVATE Falcor)
set_target_properties(PolygonSDF PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${FALCOR_RUNTIME_OUTPUT_DIRECTORY})
set_target_properties(PolygonSDF PROPERTIES VS_DEBUGGER_ENVIRONMENT "FALCOR_DEVMODE=1")

target_copy_shaders(PolygonSDF PolygonSDF)
target_copy_data_folder(PolygonSDF)
target_source_group(PolygonSDF Samples)


#### Main app executable
add_executable(PolygonSDFApplication)
target_link_libraries(PolygonSDFApplication PRIVATE Falcor PolygonSDF)
set_target_properties(PolygonSDFApplication PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${FALCOR_RUNTIME_OUTPUT_DIRECTORY})
set_target_properties(PolygonSDFApplication PROPERTIES VS_DEBUGGER_ENVIRONMENT "FALCOR_DEVMODE=1")

target_sources(PolygonSDFApplication PRIVATE
        Application/PolygonSDFApplication.cpp
        Application/PolygonSDFApplication.h
        Application/Main.cpp)


#### A separate executable for testing
add_executable(PolygonSDFTest)
target_link_libraries(PolygonSDFTest PRIVATE Falcor PolygonSDF)
set_target_properties(PolygonSDFTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${FALCOR_RUNTIME_OUTPUT_DIRECTORY})
set_target_properties(PolygonSDFTest PROPERTIES VS_DEBUGGER_ENVIRONMENT "FALCOR_DEVMODE=1")

target_sources(PolygonSDFTest PRIVATE
        Tests/Algorithm/Region/TestEdgeRegionCutWithEdges.h
        Tests/Algorithm/Region/TestEdgeRegionCutWithVertices.h
        Tests/Algorithm/Region/TestPolyCut.h
        Tests/Algorithm/Region/TestVertexRegionCutWithEdges.h
        Tests/Algorithm/Region/TestVertexRegionCutWithVertices.h

        Tests/Algorithm/TestSdfPlaneAlgorithm.h

        Tests/Editor/Aggregator/TestStackPeekingEditorAggregator.h
        Tests/Editor/Aggregator/TestStackSizeEditorAggregator.h

        Tests/Editor/Command/TestAddNewOutlineStackCommand.h
        Tests/Editor/Command/TestAddVertexStackCommand.h
        Tests/Editor/Command/TestCalculateSdfPlaneAlgorithmCommand.h
        Tests/Editor/Command/TestDeleteOutlineStackCommand.h
        Tests/Editor/Command/TestDeleteVertexStackCommand.h
        Tests/Editor/Command/TestInsertVertexStackCommand.h
        Tests/Editor/Command/TestMergeShapeWithOffsetStackCommand.h
        Tests/Editor/Command/TestMoveOutlineStackCommand.h
        Tests/Editor/Command/TestSetShapeStackCommand.h
        Tests/Editor/Command/TestUpdateVertexStackCommand.h

        Tests/Editor/Constraint/TestDeleteOutlineEditorConstraint.h
        Tests/Editor/Constraint/TestDeleteVertexEditorConstraint.h
        Tests/Editor/Constraint/TestSdfPlaneAlgorithmConstraint.h

        Tests/Editor/Consumer/TestGuiStateEditorConsumer.h
        Tests/Editor/Consumer/TestPropertyUpdatingEditorConsumer.h
        Tests/Editor/Consumer/TestVisualEditorStateChangeEditorConsumer.h

        Tests/Editor/Core/TestEditor.h

        Tests/Editor/Event/TestConstraintViolationEvent.h
        Tests/Editor/Event/TestNewStackCommandEvent.h
        Tests/Editor/Event/TestStackTransformedEvent.h
        Tests/Editor/Event/TestUnknownCommandEvent.h

        Tests/Editor/Transformation/TestClearHistoryEditorTransformation.h
        Tests/Editor/Transformation/TestUndoEditorTransformation.h

        Tests/External/catch.hpp

        Tests/Util/TestCommand.cpp
        Tests/Util/TestCommand.h
        Tests/Util/TestConsumer.cpp
        Tests/Util/TestConsumer.h
        Tests/Util/TestUtils.cpp
        Tests/Util/TestUtils.h

        Tests/Main.cpp
        )


#### A separate executable for testing
add_executable(PolygonSDFBenchmark)
target_link_libraries(PolygonSDFBenchmark PRIVATE Falcor PolygonSDF)
set_target_properties(PolygonSDFBenchmark PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${FALCOR_RUNTIME_OUTPUT_DIRECTORY})
set_target_properties(PolygonSDFBenchmark PROPERTIES VS_DEBUGGER_ENVIRONMENT "FALCOR_DEVMODE=1")

target_sources(PolygonSDFBenchmark PRIVATE
        Benchmarks/Benchmark.cpp
        Benchmarks/Benchmark.h

        Benchmarks/Main.cpp
        )
