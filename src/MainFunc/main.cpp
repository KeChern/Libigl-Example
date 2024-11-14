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

#include "Interface/MenuManager.h"
#include "Interface/RenderManager.h"
#include "Mesh/MeshCreator.h"
#include "Mesh/MeshBoolean.h"

bool key_down(igl::opengl::glfw::Viewer &viewer, unsigned char key, int modifier) {
    if (key == ' ') {
        viewer.core().is_animating = !viewer.core().is_animating;
    }
    return false;
}
#include "Utility/HelpFunc.h"
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

//    for (int i = 0; i < 10; i++) {
//        double a = 1.0, b = 5.0;
//        std::cout << "Random double between " << a << " and " << b << ": "
//                  << GetRandomDouble(a, b) << std::endl;
//    }


//    MeshCreator meshCreator;
    Mesh *cuboid = MeshCreator::CreateCuboid(Eigen::Vector3d(2, 3, 4));
    Mesh *bunny = new Mesh("../data/bunny.obj");
    bunny = MeshCreator::CreateCylinder(2, 0.5, 200);
    bunny = MeshCreator::CreateCylinder(Eigen::Vector3d(1, 1, 1), Eigen::Vector3d(2, 2, 2), 1, 6);
    bunny = MeshCreator::CreateSphere(Eigen::Vector3d(1, 1, 1), 1, 20);
    bunny = MeshCreator::CreateCone(Eigen::Vector3d(1, 1, 1), Eigen::Vector3d(2, 2, 2), 1, 100);

    Mesh *s1 = MeshCreator::CreateSphere(Eigen::Vector3d(0, 0, 0), 1, 50);
    Mesh *s2 = MeshCreator::CreateSphere(Eigen::Vector3d(3, 0, 0), 1, 50);

    s1 = MeshBoolean::MeshConnect(s1, s2);
//    std::cout<<s1->faceM.array()+200<<std::endl;



    std::vector<igl::opengl::ViewerData> DataList;
    igl::opengl::ViewerData data;
    data.set_mesh(s1->verM, s1->faceM);
    data.show_lines = true;
    data.face_based = true;
    data.double_sided = false;
    DataList.emplace_back(data);

//    std::cout<<Eigen::Vector3d::Ones()<<std::endl;

    data.set_mesh(s2->verM, s2->faceM);
//    data.show_lines = true;
//    data.face_based = true;
//    data.set_colors(Eigen::RowVector3d(0.86, 0.62, 0.86));
//    DataList.emplace_back(data);






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

