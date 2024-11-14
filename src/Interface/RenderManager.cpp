/// ========================================
///
///     RenderManager.cpp
///
///     Rendering 3D contents by libigl
///
///     by Peng Song
///
///     2020-12-01
///
/// ========================================

#include "RenderManager.h"

void RenderManager::InitViewer(igl::opengl::glfw::Viewer &viewer) {
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

void
RenderManager::RenderScene(igl::opengl::glfw::Viewer &viewer, const std::vector<igl::opengl::ViewerData> &datalist) {
    viewer.data_list.clear();

    /// We have to render mechanism first (for animating it properly)
    RenderModel(viewer, datalist);

    RenderGround(viewer, Eigen::Vector3d(0, 0, 0), 4.0, 4, 20);

    RenderGround(viewer, Eigen::Vector3d(6, 0, 0), 4.0, 4, 20);

    RenderAxes(viewer, Eigen::Vector3d(0, 0, 0), 2.0, 40);
}

void
RenderManager::RenderModel(igl::opengl::glfw::Viewer &viewer, const std::vector<igl::opengl::ViewerData> &datalist) {
    viewer.data_list = datalist;
    ModelNum = static_cast<int>(datalist.size());
}

void
RenderManager::RenderGround(igl::opengl::glfw::Viewer &viewer, const Eigen::Vector3d &origin, double size, int gridNum,
                            int sampNum) {
    double halfSize = 0.5f * size;
    double cylinderRad = 0.002f * size;

    /// 1. Create cylinders for the ground
    std::vector<Mesh *> meshList;
    Mesh *cylinder;
    for (int i = 0; i <= gridNum; i++) {
        double z = -halfSize + (i / (double) gridNum) * size;
        Eigen::Vector3d startPt = origin + Eigen::Vector3d(-halfSize, 0, z);
        Eigen::Vector3d endPt = origin + Eigen::Vector3d(halfSize, 0, z);
        cylinder = MeshCreator::CreateCylinder(startPt, endPt, cylinderRad, sampNum);
        meshList.emplace_back(cylinder);
    }

    for (int i = 0; i <= gridNum; i++) {
        double x = -halfSize + (i / (double) gridNum) * size;
        Eigen::Vector3d startPt = origin + Eigen::Vector3d(x, 0, -halfSize);
        Eigen::Vector3d endPt = origin + Eigen::Vector3d(x, 0, halfSize);
        cylinder = MeshCreator::CreateCylinder(startPt, endPt, cylinderRad, sampNum);
        meshList.push_back(cylinder);
    }

    /// 2. Create viewerData for each mesh to render it
    for (Mesh *mesh: meshList) {
        igl::opengl::ViewerData data;
        data.set_mesh(mesh->verM, mesh->faceM);
        data.set_colors(GetRGB("light gray"));
        data.show_lines = unsigned(0);
        data.face_based = true;
        viewer.data_list.emplace_back(data);
    }
    GroundNum += static_cast<int>(meshList.size());

    /// 3. Release memory for the meshList
    for (Mesh *mesh: meshList)
        delete mesh;
}

void
RenderManager::RenderAxes(igl::opengl::glfw::Viewer &viewer, const Eigen::Vector3d &origin, double size, int sampNum) {
    /// 1. Compute and specify parameters for the axes
    Eigen::Vector3d xPoint1 = origin + Eigen::Vector3d(0.9 * size, 0, 0);
    Eigen::Vector3d xPoint2 = origin + Eigen::Vector3d(1.0 * size, 0, 0);
    Eigen::Vector3d yPoint1 = origin + Eigen::Vector3d(0, 0.9 * size, 0);
    Eigen::Vector3d yPoint2 = origin + Eigen::Vector3d(0, 1.0 * size, 0);
    Eigen::Vector3d zPoint1 = origin + Eigen::Vector3d(0, 0, 0.9 * size);
    Eigen::Vector3d zPoint2 = origin + Eigen::Vector3d(0, 0, 1.0 * size);

    double cylinderRad = 0.02 * size;
    double coneRad = 0.04 * size;
    double sphereRad = 0.04 * size;

    /// 2. Create 7 meshes for the axes (3 cylinders, 3 cones, and 1 sphere)
    Mesh *cylinderX = MeshCreator::CreateCylinder(origin, xPoint1, cylinderRad, sampNum);
    Mesh *cylinderY = MeshCreator::CreateCylinder(origin, yPoint1, cylinderRad, sampNum);
    Mesh *cylinderZ = MeshCreator::CreateCylinder(origin, zPoint1, cylinderRad, sampNum);

    Mesh *coneX = MeshCreator::CreateCone(xPoint1, xPoint2, coneRad, sampNum);
    Mesh *coneY = MeshCreator::CreateCone(yPoint1, yPoint2, coneRad, sampNum);
    Mesh *coneZ = MeshCreator::CreateCone(zPoint1, zPoint2, coneRad, sampNum);

    Mesh *sphere = MeshCreator::CreateSphere(origin, sphereRad, sampNum);

    std::vector<Mesh *> meshList;
    meshList.push_back(cylinderX);
    meshList.push_back(coneX);
    meshList.push_back(cylinderY);
    meshList.push_back(coneY);
    meshList.push_back(cylinderZ);
    meshList.push_back(coneZ);
    meshList.push_back(sphere);

    /// 3. Create viewerData for each mesh to render it
    for (int i = 0; i < meshList.size(); i++) {
        Mesh *mesh = meshList[i];
        igl::opengl::ViewerData data;
        data.set_mesh(mesh->verM, mesh->faceM);

        if (i == 0 || i == 1) data.set_colors(GetRGB("red"));
        else if (i == 2 || i == 3) data.set_colors(GetRGB("green"));
        else if (i == 4 || i == 5) data.set_colors(GetRGB("blue"));
        else data.set_colors(GetRGB("gray"));

        data.show_lines = unsigned(0);
        data.face_based = true;

        viewer.data_list.emplace_back(data);
    }
    AxesNum += static_cast<int>(meshList.size());

    /// 4. Release memory for the meshList
    for (Mesh *mesh: meshList)
        delete mesh;
}

void RenderManager::ShowModel(igl::opengl::glfw::Viewer &viewer, bool is_visible) const {
    for (int i = 0; i < ModelNum; i++) {
        viewer.data_list[i].is_visible = is_visible;
    }
}

void RenderManager::ShowGround(igl::opengl::glfw::Viewer &viewer, bool is_visible) const {
    for (int i = ModelNum; i < (ModelNum + GroundNum); i++) {
        viewer.data_list[i].is_visible = is_visible;
    }
}

void RenderManager::ShowAxes(igl::opengl::glfw::Viewer &viewer, bool is_visible) const {
    for (int i = ModelNum + GroundNum; i < (ModelNum + GroundNum + AxesNum); i++) {
        viewer.data_list[i].is_visible = is_visible;
    }
}
