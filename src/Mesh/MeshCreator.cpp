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

#include "MeshCreator.h"

Mesh *MeshCreator::CreateCuboid(const Eigen::Vector3d &minPt, const Eigen::Vector3d &maxPt) {
    /// 1. Create a cuboid with the computed size
    Eigen::Vector3d sizeVec = maxPt - minPt;
    Mesh *mesh = CreateCuboid(sizeVec);

    /// 2. Compute the translation matrix
    Eigen::Vector3d center = 0.5f * (minPt + maxPt);
    Eigen::Affine3d transMat = GetTranslationMatrix(center);

    /// 3. Translate the cuboid to its computed position
    mesh->Transform(transMat);

    return mesh;
}

Mesh *MeshCreator::CreateCuboid(const Eigen::Vector3d &sizeVec) {
    std::vector<Eigen::Vector3d> verlist;
    std::vector<Eigen::Vector3i> trilist;

    /// 1. Compute vertices of the cuboid
    double minX = -0.5f * sizeVec[0];
    double minY = -0.5f * sizeVec[1];
    double minZ = -0.5f * sizeVec[2];

    double maxX = 0.5f * sizeVec[0];
    double maxY = 0.5f * sizeVec[1];
    double maxZ = 0.5f * sizeVec[2];

    verlist.emplace_back(minX, minY, maxZ);
    verlist.emplace_back(maxX, minY, maxZ);
    verlist.emplace_back(maxX, maxY, maxZ);
    verlist.emplace_back(minX, maxY, maxZ);

    verlist.emplace_back(minX, minY, minZ);
    verlist.emplace_back(maxX, minY, minZ);
    verlist.emplace_back(maxX, maxY, minZ);
    verlist.emplace_back(minX, maxY, minZ);

    /// 2. Compute triangles of the cuboid
    trilist.emplace_back(5, 4, 7);
    trilist.emplace_back(5, 7, 6);
    trilist.emplace_back(7, 2, 6);
    trilist.emplace_back(7, 3, 2);

    trilist.emplace_back(1, 0, 4);
    trilist.emplace_back(1, 3, 0);
    trilist.emplace_back(5, 6, 2);
    trilist.emplace_back(5, 2, 1);

    trilist.emplace_back(4, 5, 1);
    trilist.emplace_back(1, 2, 3);
    trilist.emplace_back(0, 3, 4);
    trilist.emplace_back(4, 3, 7);

    /// 3. Construct a triangular mesh
    Mesh *mesh = new Mesh(verlist, trilist);
    return mesh;
}

Mesh *MeshCreator::CreateCylinder(const Eigen::Vector3d &capCenterA, const Eigen::Vector3d &capCenterB, double radius,
                                  int radSamp) {

}

Mesh *MeshCreator::CreateCylinder(double length, double radius, int radSamp) {
    std::vector<Eigen::Vector3d> verlist;
    std::vector<Eigen::Vector3i> trilist;

    /// 1. Computer vertices of the cylinder

    double halfLength = 0.5f * length;
    /// Sampled points on the right cap
    for (int i = 0; i < radSamp; i++) {
        double beta = i * 2.0 * M_PI / radSamp;

        double x, y, z;
        x = halfLength;
        y = radius * cos(beta);
        z = radius * sin(beta);

        verlist.emplace_back(x, y, z);
    }
    /// Sampled points on the left cap
    for (int i = 0; i < radSamp; i++) {
        double beta = i * 2.0 * M_PI / radSamp;

        double x, y, z;
        x = -halfLength;
        y = radius * cos(beta);
        z = radius * sin(beta);

        verlist.emplace_back(x, y, z);
    }
    /// Center point of the right cap
    verlist.emplace_back(halfLength, 0, 0);
    /// Center point of the left cap
    verlist.emplace_back(-halfLength, 0, 0);

    /// 2. Computer triangles of the cylinder
    for (int i = 0; i < radSamp; i++) {
        int i1 = i;
        int j1 = (i + 1) % radSamp;
        int i2 = i + radSamp;
        int j2 = j1 + radSamp;
        trilist.emplace_back(i1, j2, j1);
        trilist.emplace_back(i2, j2, i1);
        trilist.emplace_back(i1, j1, 2 * radSamp);
        trilist.emplace_back(j2, i2, 2 * radSamp + 1);
    }

    /// 3. Construct a triangular mesh of the cylinder
    Mesh *mesh = new Mesh(verlist, trilist);

    return mesh;
}