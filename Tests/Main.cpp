#define CATCH_CONFIG_MAIN

#include "External/catch.hpp"

#include "Algorithm/Region/TestEdgeRegionCutWithEdges.h"
#include "Algorithm/Region/TestEdgeRegionCutWithVertices.h"
#include "Algorithm/Region/TestPolyCut.h"
#include "Algorithm/Region/TestVertexRegionCutWithEdges.h"
#include "Algorithm/Region/TestVertexRegionCutWithVertices.h"

#include "Algorithm/TestSdfPlaneAlgorithm.h"

#include "Editor/Aggregator/TestStackPeekingEditorAggregator.h"
#include "Editor/Aggregator/TestStackSizeEditorAggregator.h"

#include "Editor/Command/TestAddNewOutlineStackCommand.h"
#include "Editor/Command/TestAddVertexStackCommand.h"
#include "Editor/Command/TestCalculateSdfPlaneAlgorithmCommand.h"
#include "Editor/Command/TestDeleteOutlineStackCommand.h"
#include "Editor/Command/TestDeleteVertexStackCommand.h"
#include "Editor/Command/TestInsertVertexStackCommand.h"
#include "Editor/Command/TestMergeShapeWithOffsetStackCommand.h"
#include "Editor/Command/TestMoveOutlineStackCommand.h"
#include "Editor/Command/TestSetShapeStackCommand.h"
#include "Editor/Command/TestUpdateVertexStackCommand.h"

#include "Editor/Constraint/TestDeleteOutlineEditorConstraint.h"
#include "Editor/Constraint/TestDeleteVertexEditorConstraint.h"
#include "Editor/Constraint/TestSdfPlaneAlgorithmConstraint.h"

#include "Editor/Consumer/TestGuiStateEditorConsumer.h"
#include "Editor/Consumer/TestPropertyUpdatingEditorConsumer.h"
#include "Editor/Consumer/TestVisualEditorStateChangeEditorConsumer.h"

#include "Editor/Core/TestEditor.h"

#include "Editor/Event/TestConstraintViolationEvent.h"
#include "Editor/Event/TestNewStackCommandEvent.h"
#include "Editor/Event/TestStackTransformedEvent.h"
#include "Editor/Event/TestUnknownCommandEvent.h"

#include "Editor/Transformation/TestClearHistoryEditorTransformation.h"
#include "Editor/Transformation/TestUndoEditorTransformation.h"
