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

class MeshCreator {
public:
    MeshCreator() = default;
    ~MeshCreator() = default;

    /// Cuboid
    static Mesh* CreateCuboid(const Eigen::Vector3d &minPt, const Eigen::Vector3d &maxPt);
    static Mesh* CreateCuboid(const Eigen::Vector3d &sizeVec);

    /// Cylinder
    static Mesh* CreateCylinder(const Eigen::Vector3d &capCenterA, const Eigen::Vector3d &capCenterB, double radius, int radSamp);
    static Mesh* CreateCylinder(double length, double radius, int radSamp);

    /// Sphere
    static Mesh* CreateSphere(const Eigen::Vector3d &center, double radius, int radSamp);
    static Mesh* CreateSphere(double radius, int radSamp);

    /// Cone
    static Mesh* CreateCone(const Eigen::Vector3d &baseCenter, const Eigen::Vector3d &apexPoint, double radius, int radSamp);
    static Mesh* CreateCone(double length, double radius, int radSamp);
};


#endif //MESHCREATOR_H
