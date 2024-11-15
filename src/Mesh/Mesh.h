/// ========================================
///
///     Mesh.h
///
///     Mesh data structure in libigl
///
///     by Yingjie Cheng and Peng Song
///
///     2020-11-28
///
/// ========================================

#ifndef MESH_H
#define MESH_H

#include <fstream>
#include <iostream>
#include <Eigen/Geometry>

#include <igl/readOBJ.h>
#include <igl/writeOBJ.h>
#include <igl/barycenter.h>
#include <igl/doublearea.h>
#include <igl/copyleft/cgal/convex_hull.h>

#include "Utility/HelpFunc.h"
//#include "Utility/HelpStruct.h"

class Mesh {
public:
    /// Store vertices in a matrix (n,3)
    Eigen::MatrixX3d VerM;

    /// Store triangles in a matrix (m,3)
    Eigen::MatrixX3i FaceM;

public:
    Mesh() = default;
    ~Mesh() = default;

    Mesh(const Eigen::MatrixXd &verM, const Eigen::MatrixXi &faceM);
    Mesh(const std::vector<Eigen::Vector3d> &verList, const std::vector<Eigen::Vector3i> &faceList);
    explicit Mesh(const std::string &fileName);

    void VerList2VerMat(const std::vector<Eigen::Vector3d> &verList);
    void FaceList2FaceMat(const std::vector<Eigen::Vector3i> &faceList);
    void VerMat2VerList(std::vector<Eigen::Vector3d> &verList);
    void FaceMat2FaceList(std::vector<Eigen::Vector3i> &faceList);

    void ReverseNormal();

    void Transform(const Eigen::Affine3d &affineMat);
    void Transform(const Eigen::Affine3d &affineMat, Eigen::MatrixX3d &newVerM);

    void GetConvexHull();

    void SaveOBJ(const std::string &fileName);

    double ComputeVolume();
    Eigen::Vector3d ComputeGeometricCenter() const;
    void CenterMoveToOrigin();
};


#endif //MESH_H
