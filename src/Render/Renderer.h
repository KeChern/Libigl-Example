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

#ifndef RENDERER_H
#define RENDERER_H

#include <igl/opengl/glfw/Viewer.h>

class Renderer {
public:
    size_t ModelNum;
    size_t GroundNum;
    size_t AxesNum;

public:
    Renderer() = default;
    ~Renderer() = default;

    ///
    void InitViewer(igl::opengl::glfw::Viewer &viewer);

    /// Render Objects
    void RenderScene(igl::opengl::glfw::Viewer &viewer, const std::vector<igl::opengl::ViewerData> &datalist);

    void RenderModel(igl::opengl::glfw::Viewer &viewer, const std::vector<igl::opengl::ViewerData> &datalist);
    void RenderGround(igl::opengl::glfw::Viewer &viewer, const Eigen::Vector3d &origin, double size, int gridNum,
                      int sampNum);
    void RenderAxes(igl::opengl::glfw::Viewer &viewer, const Eigen::Vector3d &origin, double size, int sampNum);
//    void DrawMeshForDebug(iglViewer &viewer);

    /// Show/hide Objects
    void ShowModel(igl::opengl::glfw::Viewer &viewer, bool is_visible);
    void ShowGround(igl::opengl::glfw::Viewer &viewer, bool is_visible);
    void ShowAxes(igl::opengl::glfw::Viewer &viewer, bool is_visible);

//    void ShowInCurve(iglViewer &viewer, bool isVisible);



    /// Utility
    static void AppendDataToViewer(igl::opengl::glfw::Viewer &viewer, const std::vector<igl::opengl::ViewerData> &datalist);
};


#endif //RENDERER_H