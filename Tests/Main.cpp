#define CATCH_CONFIG_MAIN

#include "External/catch.hpp"

#include "Algorithm/Region/TestLineRegionCutWithLines.h"
#include "Algorithm/Region/TestLineRegionCutWithPoints.h"
#include "Algorithm/Region/TestPointRegionCutWithLines.h"
#include "Algorithm/Region/TestPointRegionCutWithPoints.h"
#include "Algorithm/Region/TestPolyCut.h"

#include "Algorithm/TestSdfPlaneAlgorithm.h"

#include "Editor/Aggregator/TestStackPeekingEditorAggregator.h"
#include "Editor/Aggregator/TestStackSizeEditorAggregator.h"

#include "Editor/Command/TestAddNewGroupStackCommand.h"
#include "Editor/Command/TestAddPointStackCommand.h"
#include "Editor/Command/TestCalculateSdfPlaneAlgorithmCommand.h"
#include "Editor/Command/TestDeleteGroupStackCommand.h"
#include "Editor/Command/TestDeletePointStackCommand.h"
#include "Editor/Command/TestInsertPointStackCommand.h"
#include "Editor/Command/TestMergePolygonWithOffsetStackCommand.h"
#include "Editor/Command/TestMoveGroupStackCommand.h"
#include "Editor/Command/TestSetPolygonStackCommand.h"
#include "Editor/Command/TestUpdatePointStackCommand.h"

#include "Editor/Constraint/TestDeleteGroupEditorConstraint.h"
#include "Editor/Constraint/TestDeletePointEditorConstraint.h"
#include "Editor/Constraint/TestSdfPlaneAlgorithmConstraint.h"

#include "Editor/Consumer/TestGuiStateEditorConsumer.h"
#include "Editor/Consumer/TestPropertyUpdatingEditorConsumer.h"
#include "Editor/Consumer/TestVisualEditorStateChangeEditorConsumer.h"

#include "Editor/Core/TestEditor.h"
