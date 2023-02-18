#include "DragMouseInputHandler.h"
#include "../../../Util/Deferred.h"

using namespace psdf;

DragMouseInputHandler::SharedPtr DragMouseInputHandler::create()
{
    return SharedPtr(new DragMouseInputHandler());
}

bool DragMouseInputHandler::onMouseEvent(const MouseEvent &mouseEvent)
{
    float2 mousePos = mouseEvent.pos;
    Deferred _([&](...) { this->mLastMousePosition = mousePos; });

    if (mouseEvent.type == MouseEvent::Type::Move && mIsDragging)
    {
        mDragDelta = mousePos - mLastMousePosition;
        return true;
    }

    if (mouseEvent.type == MouseEvent::Type::ButtonDown)
    {
        resetInputState();
        mIsDragging = true;
        return true;
    }

    if (mouseEvent.type == MouseEvent::Type::ButtonUp)
    {
        resetInputState();
        mIsDragging = false;
        return true;
    }
    return false;
}

void DragMouseInputHandler::resetInputState()
{
    mIsDragging = false;
    mDragDelta = float2{0};
}

bool DragMouseInputHandler::isDragging() const
{
    return mIsDragging;
}

float2 DragMouseInputHandler::getDragDelta() const
{
    return mDragDelta;
}
