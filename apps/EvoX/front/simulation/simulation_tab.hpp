#pragma once

#include <sstream>
#include <cctype>

#include "../../back/app_state.hpp"
#include "../../back/grid_fbo.hpp"
#include "simulation_constants.hpp"

namespace front::simulation
{
    // ── cell grid ─────────────────────────────────────────────────────────────────

    static void draw_cell_grid(back::app_state::AppState& state,
                                back::grid_fbo::GridFBO&   fbo,
                                ImGuiIO&                   io)
    {
        int gw = state.grid_w();
        if (gw == 0) return;

        float panel_w = state.level.show_editor ? io.DisplaySize.x - EDITOR_W : io.DisplaySize.x;
        float panel_h = io.DisplaySize.y - CONTENT_Y;

        ImGui::SetNextWindowPos({0, CONTENT_Y});
        ImGui::SetNextWindowSize({panel_w, panel_h});
        ImGui::SetNextWindowBgAlpha(0.0f);
        ImGui::Begin("##grid_panel", nullptr,
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoMove       |
            ImGuiWindowFlags_NoResize     |
            ImGuiWindowFlags_NoScrollbar);

        fbo.render(state.make_cell_grid(), gw, 1, (int)state.level.config.cell_size);

        float img_h       = state.level.config.cell_size;
        float avail_h     = panel_h - STATUS_H;
        float scroll_h    = img_h + 20.0f;
        float padding_top = (avail_h - scroll_h) * 0.5f;
        if (padding_top > 4.0f)
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + padding_top);

        ImGui::BeginChild("##grid_scroll", {panel_w - 4, scroll_h}, false,
            ImGuiWindowFlags_HorizontalScrollbar);

        ImGui::Image(fbo.imgui_id(), fbo.imgui_size(), {0, 0}, {1, 1});

        ImVec2 img_min = ImGui::GetItemRectMin();
        if (ImGui::IsItemClicked()) {
            float mx  = ImGui::GetMousePos().x - img_min.x;
            int   idx = (int)(mx / state.level.config.cell_size);
            if (idx >= 0 && idx < gw)
                state.level.select_cell(idx);
        }

        ImDrawList* draw = ImGui::GetWindowDrawList();
        float cs = state.level.config.cell_size;
        for (int i = 0; i < gw; i++) {
            float x0 = img_min.x + i * cs;
            float y0 = img_min.y;
            char lbl[16];
            snprintf(lbl, sizeof(lbl), "C%d", i);
            ImVec2 tsz = ImGui::CalcTextSize(lbl);
            draw->AddText({x0 + (cs - tsz.x) * 0.5f, y0 + (cs - tsz.y) * 0.5f},
                        IM_COL32(255, 255, 255, 180), lbl);
        }
        if (state.level.selected_cell >= 0 && state.level.selected_cell < gw) {
            float x0 = img_min.x + state.level.selected_cell * cs;
            float y0 = img_min.y;
            draw->AddRect({x0, y0}, {x0 + cs, y0 + cs},
                        IM_COL32(255, 215, 0, 255), 0, 0, 2.5f);
        }

        ImGui::EndChild();

        ImGui::Text("Cells: %d  |  Step: %d  |  %s  |  %.2f s/step",
            gw, state.level.universe.step_count,
            state.level.running ? "Running" : "Paused",
            state.level.step_interval);

        ImGui::End();
    }

    // ── universe settings content ─────────────────────────────────────────────────

    static void draw_universe_settings_content(back::app_state::AppState& state)
    {
        ImGui::Text("Universe Config");
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::SliderInt("Cells", &state.level.config.nb_cells, 1, 16);
        ImGui::Spacing();

        static int log2_max_instr = 22;
        if (ImGui::SliderInt("Max instr (2^n)", &log2_max_instr, 14, 26))
            state.level.universe.max_nb_instr_exec = 1 << log2_max_instr;
        ImGui::SameLine();
        ImGui::Text("= %d", state.level.universe.max_nb_instr_exec);
        ImGui::Spacing();

        ImGui::SliderFloat("Speed", &state.level.step_interval, 0.05f, 5.0f, "%.2f s/step");
        ImGui::Spacing();
    }

    // ── basic cell editor content ─────────────────────────────────────────────────

    static void draw_cell_basic_editor_content(back::app_state::AppState& state)
    {
        int n = (int)state.level.universe.cells.size();

        for (int i = 0; i < n; i++) {
            char lbl[16];
            snprintf(lbl, sizeof(lbl), " C%d ", i);
            bool sel = (state.level.selected_cell == i);
            if (sel)
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.55f, 0.35f, 0.05f, 1.0f));
            if (ImGui::Button(lbl, {0, 24}))
                state.level.select_cell(i);
            if (sel)
                ImGui::PopStyleColor();
            if (i < n - 1) ImGui::SameLine();
        }
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        if (state.level.selected_cell < 0 || state.level.selected_cell >= n) {
            ImGui::TextDisabled("Click a cell to edit it.");
            ImGui::Spacing();
        } else {
            bool is_void = state.level.universe.cells[state.level.selected_cell].is_void;
            ImGui::Text("Cell %d — %s", state.level.selected_cell, is_void ? "void" : "EvoX algo");
            ImGui::Spacing();

            // Reserve space below the editor for buttons + load row + save row
            float editor_h = ImGui::GetContentRegionAvail().y - 176.0f;
            if (editor_h < 60.0f) editor_h = 60.0f;

            if (ImGui::InputTextMultiline("##code",
                    state.level.editor_buf.data(), state.level.editor_buf.size(),
                    {-1, editor_h},
                    ImGuiInputTextFlags_AllowTabInput))
                state.level.editor_dirty = true;

            ImGui::Spacing();

            if (ImGui::Button("Apply")) state.level.apply_editor();
            ImGui::SameLine();
            if (ImGui::Button("Make Void")) {
                state.level.universe.set_cell_void(state.level.selected_cell);
                state.level.editor_buf[0] = '\0';
                state.level.editor_dirty  = false;
            }
            ImGui::SameLine();
            if (ImGui::Button("Reload")) state.level.load_editor();
            if (state.level.editor_dirty) {
                ImGui::SameLine();
                ImGui::TextColored({1.0f, 0.8f, 0.2f, 1.0f}, "unsaved");
            }

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();

            ImGui::Text("Load .evox file:");
            float btn_w = 60.0f;
            ImGui::SetNextItemWidth(-(btn_w + 8));
            ImGui::InputText("##load_path", state.level.load_path, sizeof(state.level.load_path));
            ImGui::SameLine();
            if (ImGui::Button("Load", {btn_w, 0}))
            {
                if (state.level.universe.load_cell_from_file(
                        state.level.selected_cell, std::string(state.level.load_path)))
                    state.level.load_editor();
            }
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Text("Save dir:");
        ImGui::SetNextItemWidth(-1);
        ImGui::InputText("##save_dir", state.level.save_dir, sizeof(state.level.save_dir));
    }

    // ── basic editor side panel ───────────────────────────────────────────────────

    static void draw_basic_editor(back::app_state::AppState& state, ImGuiIO& io)
    {
        ImGui::SetNextWindowPos({io.DisplaySize.x - EDITOR_W, CONTENT_Y});
        ImGui::SetNextWindowSize({EDITOR_W, io.DisplaySize.y - CONTENT_Y});
        ImGui::SetNextWindowBgAlpha(0.93f);
        ImGui::Begin("##editor", nullptr,
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoMove       |
            ImGuiWindowFlags_NoResize);

        ImGui::Text("Editor");
        ImGui::Separator();
        ImGui::Spacing();

        draw_universe_settings_content(state);
        ImGui::Separator();
        ImGui::Spacing();
        draw_cell_basic_editor_content(state);

        ImGui::End();
    }
} // namespace front::simulation
