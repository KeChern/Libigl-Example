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


Mesh::Mesh(const Eigen::MatrixXd &verM, const Eigen::MatrixXi &triM) {
    VerM = verM;
    FaceM = triM;
}

Mesh::Mesh(const std::vector<Eigen::Vector3d> &verList, const std::vector<Eigen::Vector3i> &faceList) {
    VerList2VerMat(verList);
    FaceList2FaceMat(faceList);
}

Mesh::Mesh(const std::string &fileName){
    igl::readOBJ(fileName, VerM, FaceM);
}

void Mesh::VerList2VerMat(const std::vector<Eigen::Vector3d> &verList) {
    VerM.resize(static_cast<int>(verList.size()), 3);
    for (int i = 0; i < verList.size(); i++) {
        VerM(i, 0) = verList[i].x();
        VerM(i, 1) = verList[i].y();
        VerM(i, 2) = verList[i].z();
    }
}

void Mesh::FaceList2FaceMat(const std::vector<Eigen::Vector3i> &faceList) {
    FaceM.resize(static_cast<int>(faceList.size()), 3);
    for (int i = 0; i < faceList.size(); i++) {
        FaceM(i, 0) = faceList[i].x();
        FaceM(i, 1) = faceList[i].y();
        FaceM(i, 2) = faceList[i].z();
    }
}

void Mesh::FaceMat2FaceList(std::vector<Eigen::Vector3i> &faceList) {
    faceList.resize(FaceM.rows());
    for (int i = 0; i < FaceM.rows(); i++) {
        faceList[i] << FaceM(i, 0), FaceM(i, 1), FaceM(i, 2);
    }
}

void Mesh::VerMat2VerList(std::vector<Eigen::Vector3d> &verList) {
    verList.resize(VerM.rows());
    for (int i = 0; i < VerM.rows(); i++) {
        verList[i] << VerM(i, 0), VerM(i, 1), VerM(i, 2);
    }
}

void Mesh::GetConvexHull() {
    Eigen::MatrixXd V;
    igl::copyleft::cgal::convex_hull(VerM, V, FaceM);
    VerM = V;
}

/// ========================================
///             Mesh Operation
/// ========================================

void Mesh::ReverseNormal() {
    for (int i = 0; i < FaceM.rows(); i++) {
        int y = FaceM(i, 1);
        int z = FaceM(i, 2);

        FaceM(i, 1) = z;
        FaceM(i, 2) = y;
    }
}

/// ========================================
///             Transform Mesh
/// ========================================

void Mesh::Transform(const Eigen::Affine3d &affineMat) {
    for (int i = 0; i < VerM.rows(); i++) {
        VerM.row(i) = (MultiplyPoint(affineMat, VerM.row(i).transpose()).transpose()).eval();
    }
}

void Mesh::Transform(const Eigen::Affine3d &affineMat, Eigen::MatrixX3d &newVerM) {
    newVerM = VerM;
    for (int i = 0; i < VerM.rows(); i++) {
        newVerM.row(i) = MultiplyPoint(affineMat, VerM.row(i).transpose()).transpose();
    }
}

/// ========================================
///                  Save
/// ========================================

void Mesh::SaveOBJ(const std::string &fileName) {
    igl::writeOBJ("../data/" + fileName, VerM, FaceM);
}

/// ========================================
///           Compute Information
/// ========================================

double Mesh::ComputeVolume() {
    Eigen::RowVector3d origin, v0, v1, v2;
    origin = Eigen::RowVector3d::Zero();
    double volume = 0;
    for (int i = 0; i < FaceM.rows(); i++) {
        v0 = VerM.row(FaceM(i, 0));
        v1 = VerM.row(FaceM(i, 1));
        v2 = VerM.row(FaceM(i, 2));
        volume += (origin - v2).dot((v1 - v2).cross(v0 - v2));
    }
    volume /= 6.0f;
    return volume;
}

Eigen::Vector3d Mesh::ComputeGeometricCenter() const{
    Eigen::MatrixXd baryCenter;
    igl::barycenter(VerM, FaceM, baryCenter);

    Eigen::VectorXd doubleArea;
    igl::doublearea(VerM, FaceM, doubleArea);

    Eigen::RowVector3d weightedCentroid = (baryCenter.array().colwise() * doubleArea.array()).colwise().sum() / doubleArea.sum();
    return weightedCentroid.transpose();
}

void Mesh::CenterMoveToOrigin(){
    Transform(GetTranslationMatrix(-ComputeGeometricCenter()));
}
