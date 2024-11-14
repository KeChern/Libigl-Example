/// ========================================
///
///     MenuManager.h
///
///     User interface setting by libigl
///
///     by Yingjie Cheng and Yucheng Sun
///
///     2020-11-26
///
/// ========================================

#include "MenuManager.h"

void MenuManager::InitMenu(igl::opengl::glfw::Viewer &viewer, igl::opengl::glfw::imgui::ImGuiMenu &menu) {
    menu.callback_draw_viewer_window = [&]() {
        /// Color Preset
        ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(0.9f, 0.9f, 0.9f, 1.00f);
        ImGui::GetStyle().Colors[ImGuiCol_TitleBg] = ImVec4(0.9f, 0.9f, 0.9f, 1.00f);
        ImGui::GetStyle().Colors[ImGuiCol_TitleBgActive] = ImVec4(0.9f, 0.9f, 0.9f, 1.00f);
        ImGui::GetStyle().Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.9f, 0.9f, 0.9f, 1.00f);

        ImGui::GetStyle().Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
        ImGui::GetStyle().Colors[ImGuiCol_FrameBgHovered] = ImVec4(1.0f, 1.0f, 1.0f, 0.50f);
        ImGui::GetStyle().Colors[ImGuiCol_FrameBgActive] = ImVec4(1.0f, 1.0f, 1.0f, 0.50f);

        ImGui::GetStyle().Colors[ImGuiCol_MenuBarBg] = ImVec4(0.9f, 0.9f, 0.9f, 1.00f);
        ImGui::GetStyle().Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);

        ImGui::GetStyle().Colors[ImGuiCol_PopupBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);

        // ImGui::TextWrapped();

        /// Define window position + size
        float menu_width = 240.f * menu.menu_scaling();

        /// Warning: do get the true windows width to relocate the menu, the viewer using highdpi (see Viewer.cpp to support highdpi display）
        int window_width, window_height;
        glfwGetWindowSize(viewer.window, &window_width, &window_height);

        ImGui::SetNextWindowPos(ImVec2(window_width - menu_width, 0.0f), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(0.0f, 0.0f), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSizeConstraints(ImVec2(menu_width, -1.0f), ImVec2(menu_width, -1.0f));
        bool is_viewer_menu_visible = true;
        ImGui::Begin("Control Panel", &is_viewer_menu_visible, ImGuiWindowFlags_NoSavedSettings);
        ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.4f);
        if (menu.callback_draw_viewer_menu) { menu.callback_draw_viewer_menu(); }
        ImGui::PopItemWidth();
        ImGui::End();
    };

    /// Add content to the default menu window
    menu.callback_draw_viewer_menu = [&]() {

        /// Global styles of UI
        float w = ImGui::GetContentRegionAvail().x;
        float p = ImGui::GetStyle().FramePadding.x;
        float half_width = (w - p) * 0.5f;

        float gap_between_headGroups = 2.0f;
        float gap_between_controlGroups = 10.0f;

        float button_verticalGap = 2.0f;
        float button_horizontalGap = 4 * p;
        float button_width = (w - button_horizontalGap) / 2.0f;

        /// ========================================
        ///          Optimization Process
        /// ========================================

        if (ImGui::CollapsingHeader("Optimization Process", ImGuiTreeNodeFlags_DefaultOpen)) {

            ImGui::Dummy(ImVec2(0.0f, gap_between_headGroups));

            if (ImGui::Button("Read Input Curve", ImVec2(button_width, 0))) {
                frame = 0;
            }

            ImGui::SameLine(0.0f, button_horizontalGap);

            if (ImGui::Button("Optimization", ImVec2(button_width, 0))) {
                is_Optimize = true;
                frame = 0;
            }

            ImGui::Dummy(ImVec2(0.0f, gap_between_controlGroups));
        }

        ///========================================
        ///                 I/O files
        /// ========================================

        if (ImGui::CollapsingHeader("I/O files", ImGuiTreeNodeFlags_DefaultOpen)) {

            ImGui::Dummy(ImVec2(0.0f, gap_between_headGroups));

            if (ImGui::Button("Read CamLinkage", ImVec2(button_width, 0))) {
                frame = 0;
            }

            ImGui::SameLine(0.0f, button_horizontalGap);

            //// save mat.dat
            if (ImGui::Button("Save CamLinkage", ImVec2(button_width, 0))) {
                frame = 0;
            }

            ImGui::Dummy(ImVec2(0.0f, gap_between_controlGroups));
        }

        /// ========================================
        ///            Operation Control
        /// ========================================

        if (ImGui::CollapsingHeader("Operation Control", ImGuiTreeNodeFlags_DefaultOpen)) {

            ImGui::Dummy(ImVec2(0.0f, gap_between_headGroups));

            if (ImGui::Button("Stop Motion", ImVec2(button_width, 0))) {
                viewer.core().is_animating = false;
            }

            ImGui::SameLine(0.0f, button_horizontalGap);

            if (ImGui::Button("Restart Motion", ImVec2(button_width, 0))) {
                viewer.core().is_animating = true;
//                is_restart = true;
            }

            ImGui::Dummy(ImVec2(0.0f, button_verticalGap));

            if (ImGui::SliderInt("Animation Speed", &AnimateSpeed, 1, 8)) {
                std::cout << "speed is modified to " << AnimateSpeed << std::endl;
            }
            ImGui::Dummy(ImVec2(0.0f, gap_between_controlGroups));
        }

        /// ========================================
        ///             Render Control
        /// ========================================

        if (ImGui::CollapsingHeader("Render Control", ImGuiTreeNodeFlags_DefaultOpen)) {

            ImGui::Dummy(ImVec2(0.0f, gap_between_headGroups));

            ImGui::SetWindowFontScale(1);

            ImGui::Text("Show Model");
            HelpMarker("Show Model");
            ImGui::SameLine(half_width, p);
            ImGui::Checkbox("##Show Model", &is_model_visible);

            ImGui::Text("Show Ground");
            HelpMarker("Show Ground");
            ImGui::SameLine(half_width, p);
            ImGui::Checkbox("##Show Ground", &is_ground_visible);

            ImGui::Text("Show Axes");
            HelpMarker("Show Axes");
            ImGui::SameLine(half_width, p);
            ImGui::Checkbox("##Show Axes", &is_axes_visible);

            ImGui::Dummy(ImVec2(0.0f, gap_between_controlGroups));
        }
    };

    auto *plugin = new igl::opengl::glfw::imgui::ImGuiPlugin();
    plugin->widgets.push_back(&menu);
    viewer.plugins.push_back(plugin);
}

/// Show tips hovering on the UI items
void MenuManager::HelpMarker(const char *content) {
    if (ImGui::IsItemHovered()) {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(content);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}
