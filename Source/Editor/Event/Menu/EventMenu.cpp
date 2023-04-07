#include "EventMenu.h"

using namespace Falcor;
using namespace psdf;

EventMenu::SharedPtr EventMenu::create(Editor::SharedPtr pEditor)
{
    return SharedPtr(new EventMenu(std::move(pEditor)));
}

EventMenu::EventMenu(Editor::SharedPtr pEditor)
    : mpEditor(std::move(pEditor)), mpGui(EventMenuGui::create()), mpConsumer(EventMenuEditorConsumer::create(mpGui))
{
    mpEditor->addConsumer(mpConsumer);
}

void EventMenu::renderGui(Gui::Window& window)
{
    mpGui->renderGui(window);
}

EventMenu::~EventMenu()
{
    mpEditor->removeConsumer(mpConsumer);
}
