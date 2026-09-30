#pragma once

#include <sstream>
#include <cctype>

#include "../../back/app_state.hpp"
#include "../../back/grid_fbo.hpp"
#include "simulation_constants.hpp"

namespace front::simulation
{
    static void draw_cell_selector_debugger(back::app_state::AppState& state, int nb_cells)
    {
        ImGui::Text("Select cell:");
        ImGui::SameLine(0, 12);

        static constexpr float CELL_SZ = 36.0f;
        ImDrawList* dl = ImGui::GetWindowDrawList();

        // draw mini-cells
        for (int i = 0; i < nb_cells; i++)
        {
            ImVec2 pos   = ImGui::GetCursorScreenPos();
            bool   non_void = !state.level.universe.cells[i].is_void;
            bool   is_selected = (state.level.selected_cell == i);

            ImU32 fill = non_void ? IM_COL32(45, 120, 55, 230) : IM_COL32(55, 55, 60, 230);
            if (is_selected)
                fill = IM_COL32(160, 110, 15, 255);
            ImU32 border = is_selected ? IM_COL32(255, 215, 0, 255) : IM_COL32(110, 110, 120, 200);

            dl->AddRectFilled(pos, {pos.x + CELL_SZ, pos.y + CELL_SZ}, fill, 4.0f);
            dl->AddRect(pos, {pos.x + CELL_SZ, pos.y + CELL_SZ}, border, 4.0f, 0, is_selected ? 2.0f : 1.0f);

            char lbl[16]; snprintf(lbl, sizeof(lbl), "C%d", i);
            ImVec2 tsz = ImGui::CalcTextSize(lbl);
            dl->AddText({pos.x + (CELL_SZ - tsz.x) * 0.5f, pos.y + (CELL_SZ - tsz.y) * 0.5f},
                        IM_COL32(240, 240, 240, 210), lbl);

            char btn_id[16]; snprintf(btn_id, sizeof(btn_id), "##gc_%d", i);
            ImGui::InvisibleButton(btn_id, {CELL_SZ, CELL_SZ});
            if (ImGui::IsItemClicked())
                state.level.select_cell(i);
            if (i < nb_cells - 1)
                ImGui::SameLine(0, 6);
        }
    }

    static void draw_debugger_editor(back::app_state::AppState& state)
    {

    }

    static void draw_debugger(back::app_state::AppState& state, ImGuiIO& io)
    {
        ImGui::SetNextWindowPos({0, CONTENT_Y});
        ImGui::SetNextWindowSize({io.DisplaySize.x, io.DisplaySize.y - CONTENT_Y});
        ImGui::SetNextWindowBgAlpha(0.93f);
        ImGui::Begin("##debugger_editor", nullptr,
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoMove       |
            ImGuiWindowFlags_NoResize);

        int n = (int)state.level.universe.cells.size();

        draw_cell_selector_debugger(state, n);

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // ── Guard: need a selected EvoX cell ─────────────────────────
        if (state.level.selected_cell < 0 || state.level.selected_cell >= n)
        {
            ImGui::TextDisabled("Click a cell to inspect it.");
            ImGui::End();
            return;
        }
        if (state.level.universe.cells[state.level.selected_cell].is_void)
        {
            ImGui::TextDisabled("Cell %d is void.", state.level.selected_cell);
            ImGui::End();
            return;
        }

        draw_debugger_editor(state);

        ImGui::End();
    }
} // namespace front::simulation
