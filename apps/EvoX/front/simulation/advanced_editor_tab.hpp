#pragma once

#include <sstream>
#include <cctype>

#include "../../back/app_state.hpp"
#include "../../back/grid_fbo.hpp"
#include "simulation_constants.hpp"

namespace front::simulation
{
    static constexpr float LIST_W  = 220.0f; 

    static void draw_cell_selector(back::app_state::AppState& state, int nb_cells)
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

    static int draw_progtein_and_gene_list(back::level::Level::EvoxSummary s_summary,
                                           int mode,
                                           int selected_progtein,
                                           int selected_gene,
                                           float available_height)
    {
        ImGui::BeginChild("##ge_list", {LIST_W, available_height}, true,
            ImGuiWindowFlags_HorizontalScrollbar);

        if (mode == 0) // progteins
        {
            for (int i = 0; i < (int)s_summary.progteins.size(); i++)
            {
                auto& p = s_summary.progteins[i];
                char lbl[80];
                snprintf(lbl, sizeof(lbl), "[%d]  %s", p.id, p.name.c_str());
                if (ImGui::Selectable(lbl, selected_progtein == i))
                    selected_progtein = i;
            }
        }
        else // genes
        {
            for (int i = 0; i < (int)s_summary.genes.size(); i++)
            {
                char lbl[32];
                snprintf(lbl, sizeof(lbl), "gene  id=%d", s_summary.genes[i].id);
                if (ImGui::Selectable(lbl, selected_gene == i)) 
                    selected_gene = i;
            }
        }

        ImGui::EndChild();

        return mode == 0 ? selected_progtein : selected_gene;
    }

    static void draw_genetic_info(back::level::Level::EvoxSummary s_summary,
                                  int mode,
                                  int selected_progtein,
                                  int selected_gene,
                                  float context_width,
                                  float available_height)
    {
        ImGui::BeginChild("##ge_content", {context_width, available_height}, true);

        if (mode == 0)
        {
            if (selected_progtein >= 0 && selected_progtein < (int)s_summary.progteins.size())
            {
                auto& p = s_summary.progteins[selected_progtein];
                int nlines = 1;
                for (char c : p.body) if (c == '\n') nlines++;
                ImGui::Text("PROGTEIN %s  id=%d  (%d lines)", p.name.c_str(), p.id, nlines);
                ImGui::Separator();
                ImGui::Spacing();
                ImGui::TextUnformatted(p.body.c_str());
            }
            else
            {
                ImGui::TextDisabled("Select a progtein from the list.");
            }
        }
        else
        {
            if (selected_gene >= 0 && selected_gene < (int)s_summary.genes.size())
            {
                auto& g = s_summary.genes[selected_gene];
                int nlines = 1;
                for (char c : g.body) if (c == '\n') nlines++;
                ImGui::Text("GENE  id=%d  (%d lines)", g.id, nlines);
                ImGui::Separator();
                ImGui::Spacing();
                ImGui::TextUnformatted(g.body.c_str());
            }
            else
            {
                ImGui::TextDisabled("Select a gene from the list.");
            }
        }

        ImGui::EndChild();
    }

    static void draw_editor_zone(back::level::Level::EvoxSummary s_summary,
                                 int mode)
    {
        // ── Two-column layout: list  |  content ──────────────────────
        static int selected_progtein = -1;
        static int selected_gene     = -1;

        float avail_h   = ImGui::GetContentRegionAvail().y;
        float content_w = ImGui::GetContentRegionAvail().x - LIST_W - 8.0f;
        if (content_w < 80.0f)
            content_w = 80.0f;

        
        // Left : progteins and genes list
        if (mode == 0) // progteins
            selected_progtein = draw_progtein_and_gene_list(s_summary, mode, selected_progtein, selected_gene, avail_h);
        else // genes
            selected_gene = draw_progtein_and_gene_list(s_summary, mode, selected_progtein, selected_gene, avail_h);

        ImGui::SameLine();

        // Right: content view
        draw_genetic_info(s_summary, mode, selected_progtein, selected_gene, content_w, avail_h);
    }

    static bool draw_choose_mode(back::app_state::AppState& state,
                                 back::level::Level::EvoxSummary s_summary)
    {
        // ── Mode selector (Progteins / Genes) ─────────────────────────
        static int mode = 0;   // 0 = progteins, 1 = genes
        ImGui::RadioButton("Progteins", &mode, 0);
        ImGui::SameLine();
        ImGui::RadioButton("Genes", &mode, 1);
        ImGui::SameLine(0, 24);
        ImGui::TextDisabled("Cell %d  |  %d progteins  |  %d genes",
            state.level.selected_cell,
            (int)s_summary.progteins.size(),
            (int)s_summary.genes.size());

        return mode;
    }

    static back::level::Level::EvoxSummary reparsing(back::app_state::AppState& state,
                                                     back::level::Level::EvoxSummary s_summary)
    {
        // ── Cached parse of editor_buf ────────────────────────────────
        // Re-parse when: selected cell changes, a step completes (step_count
        // changes), or the user applies edits (editor_dirty goes false).
        static int        s_cell      = -2;
        static int        s_step      = -1;
        static bool       s_was_dirty = true;

        bool need_reparse = (s_cell != state.level.selected_cell)
                         || (s_step != state.level.universe.step_count)
                         || (!state.level.editor_dirty && s_was_dirty);
        if (need_reparse)
        {
            s_cell    = state.level.selected_cell;
            s_step    = state.level.universe.step_count;
            s_summary = state.level.parse_evox_summary(state.level.editor_buf.data());
        }
        s_was_dirty = state.level.editor_dirty;

        return s_summary;
    }

    static void draw_evox_editor(back::app_state::AppState& state)
    {
        static back::level::Level::EvoxSummary s_summary;

        s_summary = reparsing(state, s_summary);
        bool mode = draw_choose_mode(state, s_summary);

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        draw_editor_zone(s_summary, mode);
    }

    static void draw_genetic_editor(back::app_state::AppState& state, ImGuiIO& io)
    {
        ImGui::SetNextWindowPos({0, CONTENT_Y});
        ImGui::SetNextWindowSize({io.DisplaySize.x, io.DisplaySize.y - CONTENT_Y});
        ImGui::SetNextWindowBgAlpha(0.93f);
        ImGui::Begin("##genetic_editor", nullptr,
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoMove       |
            ImGuiWindowFlags_NoResize);

        int n = (int)state.level.universe.cells.size();

        draw_cell_selector(state, n);

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

        draw_evox_editor(state);

        ImGui::End();
    }
} // namespace front::simulation
