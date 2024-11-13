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

#include <iostream>
#include <fstream>
#include <Eigen/Geometry>
#include <igl/readOBJ.h>
#include <igl/writeOBJ.h>

//#include "Utility/HelpStruct.h"
#include "Utility/HelpFunc.h"

class Mesh {
public:
    /// Store vertices in a matrix (n,3)
    Eigen::MatrixX3d verM;
    /// Store triangles in a matrix (m,3)
    Eigen::MatrixX3i triM;
//    /// Store per triangle normal in a matrix (m,3)
//    Eigen::MatrixX3d norM;
//    /// Triangles (vertex positions)
//    std::vector<Triangle*> triangles;
public:
    Mesh() = default;
    ~Mesh() = default;

    Mesh(const Eigen::MatrixXd &_verM, const Eigen::MatrixXi &_triM);
    Mesh(const std::vector<Eigen::Vector3d> &verlist, const std::vector<Eigen::Vector3i> &trilist);
    Mesh(const std::vector<Eigen::Vector3d> &verlist, int rows, int cols);
    Mesh(const std::string &filename);

    void VerList2VerMat(const std::vector<Eigen::Vector3d> &verlist);
    void TriList2TriMat(const std::vector<Eigen::Vector3i> &trilist);
    void TriMat2TriList(std::vector<Eigen::Vector3i> &trilist);
    void VerMat2VerList(std::vector<Eigen::Vector3d> &verlist);


//    void RestoreNormal();
//    void ReverseNormal();

    void Transform(const Eigen::Affine3d &mat);
    void Transform(const Eigen::Affine3d &mat, Eigen::MatrixX3d &new_verM);

    void SaveAsOBJ(const std::string &filename);
    double ComputeVolume();
};


#endif //MESH_H
