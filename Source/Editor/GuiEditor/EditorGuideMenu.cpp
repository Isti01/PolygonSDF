#include "EditorGuideMenu.h"

using namespace psdf;
using namespace Falcor;

EditorGuideMenu::SharedPtr EditorGuideMenu::create()
{
    return SharedPtr(new EditorGuideMenu());
}

void EditorGuideMenu::renderGui(Gui::Window &window)
{
    if (auto group = window.group("Editor Guide"))
    {
        group.text("Visual Editor controls:\n\n"
                   "V - Pan and Zoom\n"
                   "M - Move Vertices\n"
                   "G - Move Outlines\n"
                   "V - Pan and Zoom\n"
                   "I - Insert vertices\n"
                   "D - View algorithm result");
    }
}
