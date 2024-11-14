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

#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <igl/opengl/glfw/imgui/ImGuiMenu.h>

class MenuManager {
public:
    /// Global Variables
    int window_width = 1600;
    int window_height = 1200;

    int frame = 0;
    int AnimateSpeed = 1;

    bool is_model_visible = true;
    bool is_ground_visible = true;
    bool is_axes_visible = true;

    bool is_restart = false;
    bool is_Optimize = false;

public:
    MenuManager() = default;

    ~MenuManager() = default;

    void InitMenu(igl::opengl::glfw::Viewer &viewer, igl::opengl::glfw::imgui::ImGuiMenu &menu);

    static void HelpMarker(const char *content);
};

#endif //MENUMANAGER_H
