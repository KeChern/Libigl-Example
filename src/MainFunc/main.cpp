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

#include "Mesh/MeshCreator.h"
#include "Render/Renderer.h"
#include "Render/Menu.h"

//// Global Variables
int WindowWidth;
int WindowHeight;
int frame;
int AnimateSpeed;
bool is_restart;
bool is_Optimize;

bool is_model_visible;
bool is_ground_visible;
bool is_axes_visible;

void InitGlobalVariables() {
    WindowWidth = 1600;
    WindowHeight = 1000;

    AnimateSpeed = 1;

    is_model_visible = true;
    is_ground_visible = true;
    is_axes_visible = true;

    is_restart = false;
    frame = 0;

    is_Optimize = false;
}

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
    /// Render Engine
    Renderer renderer{};

    InitMenu(viewer, menu);
    renderer.InitViewer(viewer);
    InitGlobalVariables();


    MeshCreator meshCreator;
//    Mesh *cuboid = meshCreator.CreateCuboid(Eigen::Vector3d(2, 3, 4));
    Mesh *bunny = new Mesh("../data/bunny.obj");
    bunny = meshCreator.CreateCylinder(2, 0.5, 200);


    std::vector<igl::opengl::ViewerData> DataList;
    igl::opengl::ViewerData data;
    data.set_mesh(bunny->verM, bunny->triM);
    data.show_lines = false;
    data.face_based = true;
    DataList.emplace_back(data);

    /// Render Scene
    renderer.RenderScene(viewer, DataList);

    /// Animation
    viewer.callback_pre_draw = [&](igl::opengl::glfw::Viewer &) {
        renderer.ShowModel(viewer, is_model_visible);
        renderer.ShowGround(viewer, is_ground_visible);
        renderer.ShowAxes(viewer, is_axes_visible);

        if (viewer.core().is_animating) {
            frame += AnimateSpeed;
            Eigen::MatrixX3d new_verM;
            bunny->Transform(GetTranslationMatrix(Eigen::Vector3d(0.001, 0.001, 0) * frame), new_verM);
            viewer.data_list[0].set_vertices(new_verM);
        }

        return false;
    };

    viewer.callback_key_down = &key_down;
    viewer.launch(false, "Libigl Example", WindowWidth, WindowHeight);
    return 0;
}

