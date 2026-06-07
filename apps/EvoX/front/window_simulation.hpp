#pragma once

#include "../back/app_state.hpp"
#include "../back/grid_fbo.hpp"

namespace front::simulation
{

    static constexpr float TOOLBAR_H  = 80.0f;
    static constexpr float TABBAR_H   = 28.0f;
    static constexpr float CONTENT_Y  = TOOLBAR_H + TABBAR_H;
    static constexpr float STATUS_H   = 26.0f;
    static constexpr float EDITOR_W   = 390.0f;

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
            state.screen = back::app_state::AppScreen::MainMenu;
        }

        ImGui::End();
    }

    // ── Tab bar (thin window between toolbar and content) ─────────────────────────
    // Returns 0 = "Simulation", 1 = "Genetic editor"

    static int draw_tabbar(ImGuiIO& io)
    {
        static int active_tab = 0;

        ImGui::SetNextWindowPos({0, TOOLBAR_H});
        ImGui::SetNextWindowSize({io.DisplaySize.x, TABBAR_H});
        ImGui::SetNextWindowBgAlpha(0.90f);
        ImGui::Begin("##tabbar", nullptr,
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoMove       |
            ImGuiWindowFlags_NoResize     |
            ImGuiWindowFlags_NoScrollbar);

        if (ImGui::BeginTabBar("##main_tabs"))
        {
            if (ImGui::BeginTabItem("Simulation"))    { active_tab = 0; ImGui::EndTabItem(); }
            if (ImGui::BeginTabItem("Genetic editor")) { active_tab = 1; ImGui::EndTabItem(); }
            ImGui::EndTabBar();
        }

        ImGui::End();
        return active_tab;
    }

    // ── Tab 1: cell grid ──────────────────────────────────────────────────────────

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

    // ── Tab 1: universe settings content ─────────────────────────────────────────

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

    // ── Tab 1: basic cell editor content ─────────────────────────────────────────

    static void draw_cell_basic_editor_content(back::app_state::AppState& state)
    {
        int n = (int)state.level.universe.cells.size();

        for (int i = 0; i < n; i++)
        {
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

        if (state.level.selected_cell < 0 || state.level.selected_cell >= n)
        {
            ImGui::TextDisabled("Click a cell to edit it.");
            ImGui::Spacing();
        }
        else
        {
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

    // ── Tab 1: basic editor side panel ────────────────────────────────────────────

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

    // ── Tab 2: genetic editor ─────────────────────────────────────────────────────

    static void draw_genetic_editor(back::app_state::AppState& state, ImGuiIO& io)
    {
        ImGui::SetNextWindowPos({0, CONTENT_Y});
        ImGui::SetNextWindowSize({io.DisplaySize.x, io.DisplaySize.y - CONTENT_Y});
        ImGui::SetNextWindowBgAlpha(0.93f);
        ImGui::Begin("##genetic_editor", nullptr,
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoMove       |
            ImGuiWindowFlags_NoResize);

        // Compact cell selector
        int n = (int)state.level.universe.cells.size();
        ImGui::Text("Select cell:");
        ImGui::Spacing();

        static constexpr float CELL_SZ = 44.0f;
        ImDrawList* draw = ImGui::GetWindowDrawList();

        for (int i = 0; i < n; i++)
        {
            ImVec2 pos   = ImGui::GetCursorScreenPos();
            bool alive   = !state.level.universe.cells[i].is_void;
            bool sel     = (state.level.selected_cell == i);

            ImU32 fill   = alive ? IM_COL32(45, 120, 55, 230) : IM_COL32(55, 55, 60, 230);
            if (sel) fill = IM_COL32(160, 110, 15, 255);
            ImU32 border = sel ? IM_COL32(255, 215, 0, 255) : IM_COL32(110, 110, 120, 200);

            draw->AddRectFilled(pos, {pos.x + CELL_SZ, pos.y + CELL_SZ}, fill, 5.0f);
            draw->AddRect(pos, {pos.x + CELL_SZ, pos.y + CELL_SZ}, border, 5.0f, 0, sel ? 2.0f : 1.0f);

            char lbl[16];
            snprintf(lbl, sizeof(lbl), "C%d", i);
            ImVec2 tsz = ImGui::CalcTextSize(lbl);
            draw->AddText(
                {pos.x + (CELL_SZ - tsz.x) * 0.5f, pos.y + (CELL_SZ - tsz.y) * 0.5f},
                IM_COL32(240, 240, 240, 210), lbl);

            char btn_id[24];
            snprintf(btn_id, sizeof(btn_id), "##gc_%d", i);
            ImGui::InvisibleButton(btn_id, {CELL_SZ, CELL_SZ});
            if (ImGui::IsItemClicked())
                state.level.select_cell(i);

            if (i < n - 1) ImGui::SameLine(0, 6);
        }

        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // Placeholder
        ImGui::TextDisabled("Genetic editor — work in progress");
        ImGui::Spacing();
        ImGui::Text("Hello, world!");
        ImGui::Spacing();
        ImGui::TextWrapped(
            "This tab will host advanced visualization and editing tools "
            "for the selected cell (e.g. body inspector, instruction viewer, "
            "diff between steps, …).");

        ImGui::End();
    }

    // ── Entry point ───────────────────────────────────────────────────────────────

    static void draw_simulation(back::app_state::AppState& state,
                                back::grid_fbo::GridFBO&   fbo)
    {
        ImGuiIO& io = ImGui::GetIO();
        draw_toolbar(state, io);
        int tab = draw_tabbar(io);
        if (tab == 0)
        {
            draw_cell_grid(state, fbo, io);
            if (state.level.show_editor)
                draw_basic_editor(state, io);
        }
        else
        {
            draw_genetic_editor(state, io);
        }
    }

} // namespace front::simulation
