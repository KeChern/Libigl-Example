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
#include <igl/copyleft/cgal/convex_hull.h>

#include "Utility/HelpFunc.h"
//#include "Utility/HelpStruct.h"

class Mesh {
public:
    /// Store vertices in a matrix (n,3)
    Eigen::MatrixX3d verM;
    /// Store triangles in a matrix (m,3)
    Eigen::MatrixX3i faceM;

//    /// Store per triangle normal in a matrix (m,3)
//    Eigen::MatrixX3d norM;
//    /// Triangles (vertex positions)
//    std::vector<Triangle*> triangles;

public:
    Mesh() = default;
    ~Mesh() = default;

    Mesh(const Eigen::MatrixXd &_verM, const Eigen::MatrixXi &_faceM);
    Mesh(const std::vector<Eigen::Vector3d> &verlist, const std::vector<Eigen::Vector3i> &facelist);
    Mesh(const std::vector<Eigen::Vector3d> &verlist, int rows, int cols);
    Mesh(const std::string &filename);

    void VerList2VerMat(const std::vector<Eigen::Vector3d> &verlist);
    void FaceList2FaceMat(const std::vector<Eigen::Vector3i> &facelist);
    void VerMat2VerList(std::vector<Eigen::Vector3d> &verlist);
    void FaceMat2FaceList(std::vector<Eigen::Vector3i> &facelist);

    void Transform(const Eigen::Affine3d &mat);
    void Transform(const Eigen::Affine3d &mat, Eigen::MatrixX3d &new_verM);

    void GetConvexHull();

    void SaveOBJ(const std::string &filename);
    double ComputeVolume();
};


#endif //MESH_H
