/// ========================================
///
///     Menu.h
///
///     Making user interface by libigl
///
///     by Yingjie Cheng and Yucheng Sun
///
///     2020-11-26
///
/// ========================================

#ifndef MENU_H
#define MENU_H

#include <igl/opengl/glfw/imgui/ImGuiMenu.h>

extern int frame;
extern int AnimateSpeed;

extern bool is_model_visible;
extern bool is_ground_visible;
extern bool is_axes_visible;

extern bool is_restart;
extern bool is_Optimize;

void InitMenu(igl::opengl::glfw::Viewer &viewer, igl::opengl::glfw::imgui::ImGuiMenu &menu);

void HelpMarker(const char *content);

#endif //MENU_H
