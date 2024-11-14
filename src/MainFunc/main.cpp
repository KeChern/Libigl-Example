/// ========================================
///
///     main.cpp
///
///     Main program
///
///     by Ke Chen
///
///     2023-03-01
///
/// ========================================


#include <igl/readOBJ.h>

#include "Interface/MenuManager.h"
#include "Interface/RenderManager.h"
#include "Mesh/MeshCreator.h"


bool key_down(igl::opengl::glfw::Viewer &viewer, unsigned char key, int modifier) {
    if (key == ' ') {
        viewer.core().is_animating = !viewer.core().is_animating;
    }
    return false;
}

int main(int argc, char *argv[]) {
    /// The viewer
    igl::opengl::glfw::Viewer viewer;
    /// A menu plugin
    igl::opengl::glfw::imgui::ImGuiMenu menu;

    /// Menu Manager
    MenuManager menuMgr{};
    /// Render Manager
    RenderManager renderMgr{};

    menuMgr.InitMenu(viewer, menu);
    renderMgr.InitViewer(viewer);


    MeshCreator meshCreator;
//    Mesh *cuboid = meshCreator.CreateCuboid(Eigen::Vector3d(2, 3, 4));
    Mesh *bunny = new Mesh("../data/bunny.obj");
    bunny = MeshCreator::CreateCylinder(2, 0.5, 200);
    bunny = MeshCreator::CreateCylinder(Eigen::Vector3d(1, 1, 1), Eigen::Vector3d(2, 2, 2), 1, 6);
    bunny = MeshCreator::CreateSphere(Eigen::Vector3d(1, 1, 1), 1, 20);


    std::vector<igl::opengl::ViewerData> DataList;
    igl::opengl::ViewerData data;
    data.set_mesh(bunny->verM, bunny->triM);
    data.show_lines = false;
    data.face_based = true;
    DataList.emplace_back(data);

//    std::cout<<FLT_MIN<<std::endl;

    /// Render Scene
    renderMgr.RenderScene(viewer, DataList);

    /// Animation
    viewer.callback_pre_draw = [&](igl::opengl::glfw::Viewer &) {
        renderMgr.ShowModel(viewer, menuMgr.is_model_visible);
        renderMgr.ShowGround(viewer, menuMgr.is_ground_visible);
        renderMgr.ShowAxes(viewer, menuMgr.is_axes_visible);

        if (viewer.core().is_animating) {
            menuMgr.frame += menuMgr.AnimateSpeed;
            Eigen::MatrixX3d new_verM;
            bunny->Transform(GetTranslationMatrix(Eigen::Vector3d(0.001, 0.001, 0) * menuMgr.frame), new_verM);
            viewer.data_list[0].set_vertices(new_verM);
        }

        return false;
    };

    viewer.callback_key_down = &key_down;
    viewer.launch(false, "Libigl Example", menuMgr.window_width, menuMgr.window_height);
    return 0;
}

