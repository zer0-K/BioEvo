#pragma once

#include <sstream>
#include <cctype>

#include "../../../../src/Universe/Universe.hpp"
#include "../../../../src/Models/EvoAlgos/XASMAlgo/EvoX.hpp"
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

    static constexpr float DEBUGGER_LIST_W = 220.0f;

    static back::level::Level::EvoxSummary debugger_reparsing(back::app_state::AppState& state,
                                                              back::level::Level::EvoxSummary s_summary)
    {
        // Re-parse the cell's code when the selected cell changes or a step completes.
        static int s_cell = -2;
        static int s_step = -1;

        if (s_cell != state.level.selected_cell || s_step != state.level.universe.step_count)
        {
            s_cell    = state.level.selected_cell;
            s_step    = state.level.universe.step_count;
            s_summary = state.level.parse_evox_summary(
                state.level.universe.cells[state.level.selected_cell].evox_str.c_str());
        }

        return s_summary;
    }

    static int draw_debugger_progtein_list(const back::level::Level::EvoxSummary& s_summary,
                                           int selected_progtein,
                                           float available_height)
    {
        ImGui::BeginChild("##dbg_list", {DEBUGGER_LIST_W, available_height}, true,
            ImGuiWindowFlags_HorizontalScrollbar);

        for (int i = 0; i < (int)s_summary.progteins.size(); i++)
        {
            auto& p = s_summary.progteins[i];
            char lbl[80];
            snprintf(lbl, sizeof(lbl), "[%d]  %s", p.id, p.name.c_str());
            if (ImGui::Selectable(lbl, selected_progtein == i))
                selected_progtein = i;
        }

        ImGui::EndChild();

        return selected_progtein;
    }

    static void draw_breakpoint_panel(back::app_state::AppState& state,
                                      const back::level::Level::EvoxSummary& s_summary,
                                      int selected_progtein,
                                      float available_height)
    {
        static int  s_clicked_progtein = -1;   // progtein for which the button was clicked

        ImGui::BeginChild("##dbg_breakpoints", {0, available_height}, true);

        if (selected_progtein >= 0 && selected_progtein < (int)s_summary.progteins.size())
        {
            auto& p = s_summary.progteins[selected_progtein];
            char lbl[64];
            snprintf(lbl, sizeof(lbl), "Add breakpoint for progtein %d", p.id);
            if (ImGui::Button(lbl))
            {
                s_clicked_progtein = selected_progtein;
                state.level.universe.build();
                auto place = state.level.universe.universe->get_places()[state.level.selected_cell];
                auto evox_individual = std::dynamic_pointer_cast<EvoX>(place->get_entity());
                evox_individual->bio_debug->activated = true;
                evox_individual->bio_debug->add_breakpoint_at_progtein(p.id);
            }
        }
        else
        {
            ImGui::TextDisabled("Select a progtein from the list.");
        }

        ImGui::EndChild();
    }

    static void draw_debugger_editor(back::app_state::AppState& state)
    {
        if (state.level.universe.cells[state.level.selected_cell].is_void)
            return;
        
        if(!state.level.universe.is_built())
            state.level.universe.build();

        static back::level::Level::EvoxSummary s_summary;
        static int selected_progtein = -1;

        s_summary = debugger_reparsing(state, s_summary);

        ImGui::TextDisabled("Cell %d  |  %d progteins",
            state.level.selected_cell, (int)s_summary.progteins.size());
        ImGui::Spacing();

        float avail_h = ImGui::GetContentRegionAvail().y;

        // Left : progteins list
        selected_progtein = draw_debugger_progtein_list(s_summary, selected_progtein, avail_h);

        ImGui::SameLine();

        // Right: breakpoint actions for the selected progtein
        draw_breakpoint_panel(state, s_summary, selected_progtein, avail_h);
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
