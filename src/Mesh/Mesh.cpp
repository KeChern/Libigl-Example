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
    triM = _triM;
}

Mesh::Mesh(const std::vector<Eigen::Vector3d> &verlist, const std::vector<Eigen::Vector3i> &trilist) {
    verM.resize(static_cast<int>(verlist.size()), 3);
    for (int i = 0; i < verlist.size(); i++) {
        verM(i, 0) = verlist[i].x();
        verM(i, 1) = verlist[i].y();
        verM(i, 2) = verlist[i].z();
    }

    triM.resize(static_cast<int>(trilist.size()), 3);
    for (int i = 0; i < trilist.size(); i++) {
        triM(i, 0) = trilist[i].x();
        triM(i, 1) = trilist[i].y();
        triM(i, 2) = trilist[i].z();
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

    std::vector<Eigen::Vector3i> trilist;

    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < cols - 1; j++) {
            int id = i * cols + j;
            trilist.emplace_back(id, id + cols, id + 1);
            trilist.emplace_back(id + 1, id + cols, id + cols + 1);
        }
    }
    triM.resize(static_cast<int>(trilist.size()), 3);
    for (int i = 0; i < trilist.size(); i++) {
        triM(i, 0) = trilist[i].x();
        triM(i, 1) = trilist[i].y();
        triM(i, 2) = trilist[i].z();
    }
}

Mesh::Mesh(const std::string &filename){
    igl::readOBJ(filename, verM, triM);
}

void Mesh::VerList2VerMat(const std::vector<Eigen::Vector3d> &verlist) {
    verM.resize(static_cast<int>(verlist.size()), 3);
    for (int i = 0; i < verlist.size(); i++) {
        verM(i, 0) = verlist[i].x();
        verM(i, 1) = verlist[i].y();
        verM(i, 2) = verlist[i].z();
    }
}

void Mesh::TriList2TriMat(const std::vector<Eigen::Vector3i> &trilist) {
    triM.resize(static_cast<int>(trilist.size()), 3);
    for (int i = 0; i < trilist.size(); i++) {
        triM(i, 0) = trilist[i].x();
        triM(i, 1) = trilist[i].y();
        triM(i, 2) = trilist[i].z();
    }
}

void Mesh::TriMat2TriList(std::vector<Eigen::Vector3i> &trilist) {
    trilist.resize(triM.rows());
    for (int i = 0; i < triM.rows(); i++) {
        trilist[i] << triM(i, 0), triM(i, 1), triM(i, 2);
    }
}

void Mesh::VerMat2VerList(std::vector<Eigen::Vector3d> &verlist) {
    verlist.resize(verM.rows());
    for (int i = 0; i < verM.rows(); i++) {
        verlist[i] << verM(i, 0), verM(i, 1), verM(i, 2);
    }
}

//void Mesh::RestoreNormal() {
//    norM.resize(static_cast<int>(triangles.size()), 3);
//    for (int i = 0; i < triangles.size(); i++) {
//        norM(i, 0) = triangles[i]->normal.x();
//        norM(i, 1) = triangles[i]->normal.y();
//        norM(i, 2) = triangles[i]->normal.z();
//    }
//}

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

void Mesh::SaveAsOBJ(const std::string &filename) {
    igl::writeOBJ("../data/" + filename, verM, triM);
}

/// ========================================
///           Compute Information
/// ========================================

double Mesh::ComputeVolume() {
    Eigen::RowVector3d origin, v0, v1, v2;
    origin = Eigen::RowVector3d::Zero();
    double volume = 0;
    for (int i = 0; i < triM.rows(); i++) {
        v0 = verM.row(triM(i, 0));
        v1 = verM.row(triM(i, 1));
        v2 = verM.row(triM(i, 2));
        volume += (origin - v2).dot((v1 - v2).cross(v0 - v2));
    }
    volume /= 6.0f;
    return volume;
}
