/// ========================================
///
///     Mesh.cpp
///
///     Mesh data structure in libigl
///
///     by Yingjie Cheng and Peng Song
///
///     2020-11-28
///
/// ========================================

#include "Mesh.h"

Mesh::Mesh(const Eigen::MatrixXd &_verM, const Eigen::MatrixXi &_triM) {
    verM = _verM;
    faceM = _triM;
}

Mesh::Mesh(const std::vector<Eigen::Vector3d> &verlist, const std::vector<Eigen::Vector3i> &facelist) {
    verM.resize(static_cast<int>(verlist.size()), 3);
    for (int i = 0; i < verlist.size(); i++) {
        verM(i, 0) = verlist[i].x();
        verM(i, 1) = verlist[i].y();
        verM(i, 2) = verlist[i].z();
    }

    faceM.resize(static_cast<int>(facelist.size()), 3);
    for (int i = 0; i < facelist.size(); i++) {
        faceM(i, 0) = facelist[i].x();
        faceM(i, 1) = facelist[i].y();
        faceM(i, 2) = facelist[i].z();
    }
}

Mesh::Mesh(const std::vector<Eigen::Vector3d> &verlist, int rows, int cols) {
    if (verlist.size() != rows * cols)
        std::cout << " rows * cols is NOT equal to size of vector!" << std::endl;

    verM.resize(static_cast<int>(verlist.size()), 3);
    for (int i = 0; i < verlist.size(); i++) {
        verM(i, 0) = verlist[i].x();
        verM(i, 1) = verlist[i].y();
        verM(i, 2) = verlist[i].z();
    }
    if (rows < 2 || cols < 2)
        std::cout << "rows/cols is less than 2!" << std::endl;

    std::vector<Eigen::Vector3i> facelist;

    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < cols - 1; j++) {
            int id = i * cols + j;
            facelist.emplace_back(id, id + cols, id + 1);
            facelist.emplace_back(id + 1, id + cols, id + cols + 1);
        }
    }
    faceM.resize(static_cast<int>(facelist.size()), 3);
    for (int i = 0; i < facelist.size(); i++) {
        faceM(i, 0) = facelist[i].x();
        faceM(i, 1) = facelist[i].y();
        faceM(i, 2) = facelist[i].z();
    }
}

Mesh::Mesh(const std::string &filename){
    igl::readOBJ(filename, verM, faceM);
}

void Mesh::VerList2VerMat(const std::vector<Eigen::Vector3d> &verlist) {
    verM.resize(static_cast<int>(verlist.size()), 3);
    for (int i = 0; i < verlist.size(); i++) {
        verM(i, 0) = verlist[i].x();
        verM(i, 1) = verlist[i].y();
        verM(i, 2) = verlist[i].z();
    }
}

void Mesh::FaceList2FaceMat(const std::vector<Eigen::Vector3i> &facelist) {
    faceM.resize(static_cast<int>(facelist.size()), 3);
    for (int i = 0; i < facelist.size(); i++) {
        faceM(i, 0) = facelist[i].x();
        faceM(i, 1) = facelist[i].y();
        faceM(i, 2) = facelist[i].z();
    }
}

void Mesh::FaceMat2FaceList(std::vector<Eigen::Vector3i> &facelist) {
    facelist.resize(faceM.rows());
    for (int i = 0; i < faceM.rows(); i++) {
        facelist[i] << faceM(i, 0), faceM(i, 1), faceM(i, 2);
    }
}

void Mesh::VerMat2VerList(std::vector<Eigen::Vector3d> &verlist) {
    verlist.resize(verM.rows());
    for (int i = 0; i < verM.rows(); i++) {
        verlist[i] << verM(i, 0), verM(i, 1), verM(i, 2);
    }
}

void Mesh::GetConvexHull() {
    Eigen::MatrixXd V;
    igl::copyleft::cgal::convex_hull(verM, V, faceM);
    verM = V;
}

/// ========================================
///             Mesh Operation
/// ========================================

//void Mesh::ReverseNormal() {
//    for (int i = 0; i < triM.rows(); i++) {
//        int y = triM(i, 1);
//        int z = triM(i, 2);
//
//        triM(i, 1) = z;
//        triM(i, 2) = y;
//    }
//
////    GetMeshTriangles();
//}

/// ========================================
///             Transform Mesh
/// ========================================

void Mesh::Transform(const Eigen::Affine3d &mat) {
    for (int i = 0; i < verM.rows(); i++) {
        verM.row(i) = (MultiplyPoint(mat, verM.row(i).transpose()).transpose()).eval();
    }
}

void Mesh::Transform(const Eigen::Affine3d &mat, Eigen::MatrixX3d &new_verM) {
    new_verM = verM;
    for (int i = 0; i < verM.rows(); i++) {
        new_verM.row(i) = MultiplyPoint(mat, verM.row(i).transpose()).transpose();
    }
}

/// ========================================
///                  Save
/// ========================================

void Mesh::SaveOBJ(const std::string &filename) {
    igl::writeOBJ("../data/" + filename, verM, faceM);
}

/// ========================================
///           Compute Information
/// ========================================

double Mesh::ComputeVolume() {
    Eigen::RowVector3d origin, v0, v1, v2;
    origin = Eigen::RowVector3d::Zero();
    double volume = 0;
    for (int i = 0; i < faceM.rows(); i++) {
        v0 = verM.row(faceM(i, 0));
        v1 = verM.row(faceM(i, 1));
        v2 = verM.row(faceM(i, 2));
        volume += (origin - v2).dot((v1 - v2).cross(v0 - v2));
    }
    volume /= 6.0f;
    return volume;
}
