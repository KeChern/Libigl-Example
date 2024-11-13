/// ========================================
///
///     Renderer.h
///
///     Rendering 3D contents by libigl
///
///     by Peng Song
///
///     2020-12-01
///
/// ========================================

#include "Renderer.h"

void Renderer::InitViewer(igl::opengl::glfw::Viewer &viewer) {
    /// Animation
    viewer.core().animation_max_fps = 60.0;
    viewer.core().is_animating = false;

//    viewer.data().face_based = true;
    viewer.core().background_color.setConstant(1.0f);
//    viewer.core().background_color = Eigen::RowVector4f(1, 1, 1, 0);

    /// Light
    viewer.core().lighting_factor = 0.3;
    viewer.core().light_position = Eigen::Vector3f(0.0, 0.0, 0.3);

    /// Camera
    viewer.core().camera_zoom = 0.9;
    viewer.core().camera_eye = Eigen::Vector3f(6, 6, 6);
    viewer.core().camera_dfar = 10000;
    viewer.core().camera_dnear = 0.01;

    viewer.core().set_rotation_type(igl::opengl::ViewerCore::ROTATION_TYPE_TRACKBALL);

    Eigen::Quaternionf angle;
    angle.x() = 0.0f;
    angle.y() = 0.0f;
    angle.z() = 0.0f;
    angle.w() = 1.0f;
    viewer.core().trackball_angle = angle;
}

void Renderer::RenderScene(igl::opengl::glfw::Viewer &viewer, const std::vector<igl::opengl::ViewerData> &datalist) {
//    viewer.data_list.clear();

    /// We have to render mechanism first (for animating it properly)
    RenderModel(viewer, datalist);
    RenderGround(viewer, Eigen::Vector3d(0, 0, 0), 300.0, 6, 20);
    RenderAxes(viewer, Eigen::Vector3d(0, 0, 0), 50.0, 40);

}

void Renderer::RenderModel(igl::opengl::glfw::Viewer &viewer, const std::vector<igl::opengl::ViewerData> &datalist) {
    viewer.data_list = datalist;
    ModelNum = datalist.size();
}

void Renderer::RenderGround(igl::opengl::glfw::Viewer &viewer, const Eigen::Vector3d &origin, double size, int gridNum,
                            int sampNum) {

}

void Renderer::RenderAxes(igl::opengl::glfw::Viewer &viewer, const Eigen::Vector3d &origin, double size, int sampNum) {

}

void Renderer::ShowModel(igl::opengl::glfw::Viewer &viewer, bool is_visible) {

}

void Renderer::ShowGround(igl::opengl::glfw::Viewer &viewer, bool is_visible) {

}

void Renderer::ShowAxes(igl::opengl::glfw::Viewer &viewer, bool is_visible) {

}


void
Renderer::AppendDataToViewer(igl::opengl::glfw::Viewer &viewer, const std::vector<igl::opengl::ViewerData> &datalist) {
    for (const auto &data: datalist) {
        viewer.data_list.emplace_back(data);
    }
}
