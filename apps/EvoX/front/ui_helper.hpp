#pragma once

namespace front
{
    static void CenterText(const char* text)
    {
        float win_width = ImGui::GetContentRegionAvail().x;
        float txt_width = ImGui::CalcTextSize(text).x;
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (win_width - txt_width) * 0.5f);
        ImGui::TextUnformatted(text);
    }

    static bool CenterButton(const char* label, ImVec2 size = {200, 40})
    {
        float win_width = ImGui::GetContentRegionAvail().x;
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (win_width - size.x) * 0.5f);
        return ImGui::Button(label, size);
    }
}
