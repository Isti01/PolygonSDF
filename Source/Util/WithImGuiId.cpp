#include "WithImGuiId.h"

#include <imgui.h>

using namespace psdf;

WithImGuiId::WithImGuiId(int id)
{
    ImGui::PushID(id);
}

WithImGuiId::WithImGuiId(const char *id)
{
    ImGui::PushID(id);
}

WithImGuiId::~WithImGuiId()
{
    ImGui::PopID();
}
