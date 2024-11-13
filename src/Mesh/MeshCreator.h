/// ========================================
///
///     MeshCreator.h
///
///     Create some common meshes
///
///     by Yingjie Cheng and Peng Song
///
///     2020-11-28
///
/// ========================================

#ifndef MESHCREATOR_H
#define MESHCREATOR_H

#include "Mesh/Mesh.h"
#include <Eigen/Core>


class MeshCreator {
public:
    MeshCreator() = default;
    ~MeshCreator() = default;

    /// Cuboid
    Mesh* CreateCuboid(const Eigen::Vector3d &minPt, const Eigen::Vector3d &maxPt);
    static Mesh* CreateCuboid(const Eigen::Vector3d &sizeVec);

    /// Cylinder
    Mesh* CreateCylinder(const Eigen::Vector3d &capCenterA, const Eigen::Vector3d &capCenterB, double radius, int radSamp);
    Mesh* CreateCylinder(double length, double radius, int radSamp);


};


#endif //MESHCREATOR_H
