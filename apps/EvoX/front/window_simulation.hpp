#pragma once

#include "../back/app_state.hpp"
#include "../back/grid_fbo.hpp"

namespace front::simulation
{

    static constexpr float TOOLBAR_H = 80.0f;
    static constexpr float STATUS_H  = 26.0f;
    static constexpr float EDITOR_W  = 390.0f;

    // ── Toolbar ───────────────────────────────────────────────────────────────────

    static void draw_toolbar(back::app_state::AppState& state, ImGuiIO& io)
    {
        ImGui::SetNextWindowPos({0, 0});
        ImGui::SetNextWindowSize({io.DisplaySize.x, TOOLBAR_H});
        ImGui::SetNextWindowBgAlpha(0.88f);
        ImGui::Begin("##toolbar", nullptr,
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoMove       |
            ImGuiWindowFlags_NoResize     |
            ImGuiWindowFlags_NoScrollbar);

        ImGui::SetCursorPosY(10);

        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
        front::common::CenterText(state.level.config.experiment_name.c_str());
        ImGui::PopFont();
        ImGui::Spacing();
        ImGui::Separator();

        if (ImGui::Button(state.level.running ? "  Pause  " : "  Play  "))
            state.level.running = !state.level.running;
        ImGui::SameLine();

        if (ImGui::Button("  Step  "))
        {
            state.level.running = false;
            if (state.level.editor_dirty) state.level.apply_editor();
            state.level.universe.step();
            if (!state.level.editor_dirty) state.level.load_editor();
        }
        ImGui::SameLine();

        if (ImGui::Button("  Reset  "))
        {
            state.level.running = false;
            state.level.universe.reset();
            state.level.load_editor();
        }
        ImGui::SameLine();

        if (ImGui::Button("  Save  "))
            state.level.universe.save_snapshot(std::string(state.level.save_dir));
        ImGui::SameLine();

        if (ImGui::Button(state.level.show_editor ? "Hide Editor" : "Show Editor"))
            state.level.show_editor = !state.level.show_editor;
        ImGui::SameLine();

        ImGui::Text("Step: %d", state.level.universe.step_count);

        if (!state.level.universe.last_error.empty())
        {
            ImGui::SameLine();
            ImGui::TextColored({1.0f, 0.35f, 0.35f, 1.0f},
                "| %s", state.level.universe.last_error.c_str());
        }

        ImGui::SameLine(io.DisplaySize.x - 150);
        if (ImGui::Button("  Main Menu  "))
        {
            state.exit_simulation();
            state.screen  = back::app_state::AppScreen::MainMenu;
        }

        ImGui::End();
    }

    // ── Cell grid ─────────────────────────────────────────────────────────────────

    static void draw_cell_grid(back::app_state::AppState& state,
                                back::grid_fbo::GridFBO&   fbo,
                                ImGuiIO&                   io)
    {
        int gw = state.grid_w();
        if (gw == 0) return;

        float panel_w = state.level.show_editor ? io.DisplaySize.x - EDITOR_W : io.DisplaySize.x;
        float panel_h = io.DisplaySize.y - TOOLBAR_H;

        ImGui::SetNextWindowPos({0, TOOLBAR_H});
        ImGui::SetNextWindowSize({panel_w, panel_h});
        ImGui::SetNextWindowBgAlpha(0.0f);
        ImGui::Begin("##grid_panel", nullptr,
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoMove       |
            ImGuiWindowFlags_NoResize     |
            ImGuiWindowFlags_NoScrollbar);

        // Render alive/void state into FBO
        fbo.render(state.make_cell_grid(), gw, 1, (int)state.level.config.cell_size);

        // Centre the cell strip vertically in the available area
        float img_h      = state.level.config.cell_size;
        float avail_h    = panel_h - STATUS_H;
        float scroll_h   = img_h + 20.0f;   // +20 for scrollbar
        float padding_top = (avail_h - scroll_h) * 0.5f;
        if (padding_top > 4.0f)
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + padding_top);

        ImGui::BeginChild("##grid_scroll", {panel_w - 4, scroll_h}, false,
            ImGuiWindowFlags_HorizontalScrollbar);

        ImGui::Image(fbo.imgui_id(), fbo.imgui_size(), {0, 0}, {1, 1});

        // Click → select cell
        ImVec2 img_min = ImGui::GetItemRectMin();
        if (ImGui::IsItemClicked()) {
            float mx  = ImGui::GetMousePos().x - img_min.x;
            int   idx = (int)(mx / state.level.config.cell_size);
            if (idx >= 0 && idx < gw)
                state.level.select_cell(idx);
        }

        // DrawList overlay: labels + selection border
        ImDrawList* draw = ImGui::GetWindowDrawList();
        float cs = state.level.config.cell_size;
        for (int i = 0; i < gw; i++) {
            float x0 = img_min.x + i * cs;
            float y0 = img_min.y;

            // Cell label ("C0", "C1", …)
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

        // Status bar
        ImGui::Text("Cells: %d  |  Step: %d  |  %s  |  %.2f s/step",
            gw, state.level.universe.step_count,
            state.level.running ? "Running" : "Paused",
            state.level.step_interval);

        ImGui::End();
    }

    // ── Editor panel ─────────────────────────────────────────────────────────

    static void draw_universe_settings(back::app_state::AppState& state, ImGuiIO& io)
    {
        ImGui::SetNextWindowPos({io.DisplaySize.x - EDITOR_W, TOOLBAR_H});
        ImGui::SetNextWindowSize({EDITOR_W, 200.0f});
        ImGui::SetNextWindowBgAlpha(0.93f);
        ImGui::Begin("##universe_editor", nullptr,
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoMove       |
            ImGuiWindowFlags_NoResize);

        ImGui::Text("Universe Config");
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::SliderInt("Cells", &state.level.config.nb_cells, 1, 16);
        ImGui::Spacing();

        // Log-scale slider for max instructions: 2^16 .. 2^26
        static int log2_max_instr = 22;
        if (ImGui::SliderInt("Max instr (2^n)", &log2_max_instr, 14, 26))
            state.level.universe.max_nb_instr_exec = 1 << log2_max_instr;
        ImGui::SameLine();
        ImGui::Text("= %d", state.level.universe.max_nb_instr_exec);
        ImGui::Spacing();

        ImGui::SliderInt("Stack init", &state.level.universe.data_stack_init, 50, 500);

        ImGui::Spacing();

        ImGui::SliderFloat("Speed", &state.level.step_interval, 0.05f, 5.0f, "%.2f s/step");
        ImGui::SameLine();

        ImGui::Spacing();
        ImGui::Spacing();

        ImGui::End();
    }

    static void draw_cell_editor(back::app_state::AppState& state, ImGuiIO& io)
    {
        ImGui::SetNextWindowPos({io.DisplaySize.x - EDITOR_W, TOOLBAR_H + 200.0f});
        ImGui::SetNextWindowSize({EDITOR_W, io.DisplaySize.y - TOOLBAR_H - 200.0f});
        ImGui::SetNextWindowBgAlpha(0.93f);
        ImGui::Begin("##cell_editor", nullptr,
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoMove       |
            ImGuiWindowFlags_NoResize);

        ImGui::Text("Cell Editor");
        ImGui::Separator();
        ImGui::Spacing();

        // ── Cell selector ─────────────────────────────────────────────
        int n = (int)state.level.universe.cells.size();
        for (int i = 0; i < n; i++) {
            char lbl[16];
            snprintf(lbl, sizeof(lbl), " C%d ", i);
            bool sel = (state.level.selected_cell == i);
            if (sel)
                ImGui::PushStyleColor(ImGuiCol_Button,
                                    ImVec4(0.55f, 0.35f, 0.05f, 1.0f));
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
        } else {
            bool is_void = state.level.universe.cells[state.level.selected_cell].is_void;
            ImGui::Text("Cell %d — %s", state.level.selected_cell, is_void ? "void" : "EvoX algo");
            ImGui::Spacing();

            // ── Text editor ───────────────────────────────────────────
            // Reserve space: total height minus toolbar, separator, buttons, controls
            float editor_h = io.DisplaySize.y - TOOLBAR_H - 220.0f;
            if (editor_h < 60.0f) editor_h = 60.0f;

            if (ImGui::InputTextMultiline("##code",
                    state.level.editor_buf.data(), state.level.editor_buf.size(),
                    {-1, editor_h},
                    ImGuiInputTextFlags_AllowTabInput))
                state.level.editor_dirty = true;

            ImGui::Spacing();

            // ── Action buttons ────────────────────────────────────────
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

            // ── Load from file ────────────────────────────────────────
            ImGui::Text("Load .evox file:");
            float btn_w = 60.0f;
            ImGui::SetNextItemWidth(-(btn_w + 8));
            ImGui::InputText("##load_path", state.level.load_path, sizeof(state.level.load_path));
            ImGui::SameLine();
            if (ImGui::Button("Load", {btn_w, 0})) {
                if (state.level.universe.load_cell_from_file(
                        state.level.selected_cell, std::string(state.level.load_path)))
                    state.level.load_editor();
            }
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // ── Other controls (always visible) ──────────────────────
        ImGui::Spacing();
        ImGui::Text("Save dir:");
        ImGui::SetNextItemWidth(-1);
        ImGui::InputText("##save_dir", state.level.save_dir, sizeof(state.level.save_dir));

        ImGui::End();
    }

    static void draw_editor(back::app_state::AppState& state, ImGuiIO& io)
    {
        ImGui::SetNextWindowPos({io.DisplaySize.x - EDITOR_W, TOOLBAR_H});
        ImGui::SetNextWindowSize({EDITOR_W, io.DisplaySize.y - TOOLBAR_H});
        ImGui::SetNextWindowBgAlpha(0.85f);
        ImGui::Begin("##editor", nullptr,
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoMove       |
            ImGuiWindowFlags_NoResize);

        ImGui::Text("Editor");
        ImGui::Separator();
        ImGui::Spacing();

        draw_universe_settings(state, io);
        draw_cell_editor(state, io);

        ImGui::End();
    }
 
    // ── Entry point ───────────────────────────────────────────────────────────────

    static void DrawSimulation(back::app_state::AppState& state,
                                back::grid_fbo::GridFBO&   fbo)
    {
        ImGuiIO& io = ImGui::GetIO();
        draw_toolbar(state, io);
        draw_cell_grid(state, fbo, io);
        if (state.level.show_editor)
        {
            draw_editor(state, io);
        }
    }

} // namespace front::simulation
