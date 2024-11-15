/// ========================================
///
///     RenderManager.h
///
///     Rendering 3D contents by libigl
///
///     by Peng Song
///
///     2020-12-01
///
/// ========================================

#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include <igl/opengl/glfw/Viewer.h>

#include "Mesh/MeshCreator.h"

class RenderManager {
public:
    int ModelNum = 0;
    int GroundNum = 0;
    int AxesNum = 0;

public:
    RenderManager() = default;
    ~RenderManager() = default;

    ///
    static void InitViewer(igl::opengl::glfw::Viewer &viewer);

    /// Render Objects
    void RenderScene(igl::opengl::glfw::Viewer &viewer, const std::vector<igl::opengl::ViewerData> &datalist);

    void RenderModel(igl::opengl::glfw::Viewer &viewer, const std::vector<igl::opengl::ViewerData> &datalist);
    void RenderGround(igl::opengl::glfw::Viewer &viewer, const Eigen::Vector3d &origin, double size, int gridNum,
                      int sampNum);
    void RenderAxes(igl::opengl::glfw::Viewer &viewer, const Eigen::Vector3d &origin, double size, int sampNum);
//    void DrawMeshForDebug(iglViewer &viewer);

    /// Show/hide Objects
    void ShowModel(igl::opengl::glfw::Viewer &viewer, bool is_visible) const;
    void ShowGround(igl::opengl::glfw::Viewer &viewer, bool is_visible) const;
    void ShowAxes(igl::opengl::glfw::Viewer &viewer, bool is_visible) const;

//    void ShowInCurve(iglViewer &viewer, bool isVisible);
};


#endif //RENDERMANAGER_H
