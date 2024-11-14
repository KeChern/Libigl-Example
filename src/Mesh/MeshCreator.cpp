/// ========================================
///
///     MeshCreator.cpp
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
    /// 1. Create a cylinder with the given radius and computed length
    double length = (capCenterA - capCenterB).norm();
    Mesh *mesh = CreateCylinder(length, radius, radSamp);

    /// 2. Compute the translation matrix
    Eigen::Vector3d center = 0.5f * (capCenterA + capCenterB);
    Eigen::Affine3d transMat = GetTranslationMatrix(center);

    /// 3. Compute the rotation matrix (note: default cylinder is aligned with x-axis)
    Eigen::Vector3d xAxis = {1, 0, 0};
    Eigen::Vector3d vec = (capCenterB - capCenterA).normalized();
    Eigen::Affine3d rotMat = GetRotationMatrix(xAxis, vec);

    /// 4. Compute the trannsform matrix on the cylinder
    Eigen::Affine3d affineMat = transMat * rotMat;

    /// 5. Transform the cylinder to its target position and orientation
    mesh->Transform(affineMat);
    return mesh;
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

Mesh *MeshCreator::CreateSphere(const Eigen::Vector3d &center, double radius, int radSamp) {
    Mesh *mesh = CreateSphere(radius, radSamp);
    mesh->Transform(GetTranslationMatrix(center));
    return mesh;
}

Mesh *MeshCreator::CreateSphere(double radius, int radSamp) {
    std::vector<Eigen::Vector3d> verlist;
    std::vector<Eigen::Vector3i> trilist;

    int polarSamp = radSamp / 2;
    int azimuSamp = radSamp;

    /// 1. Compute vertices of the sphere
    int midNum = (polarSamp - 1) * azimuSamp;
    verlist.reserve(midNum + 2);
    for (int i = 1; i < polarSamp; i++) {
        double alpha = M_PI_2 - M_PI * i / polarSamp;
        for (int j = 0; j < azimuSamp; j++) {
            double beta = j * 2.0 * M_PI / azimuSamp;
            double x = radius * cos(alpha) * cos(beta);
            double y = radius * cos(alpha) * sin(beta);
            double z = radius * sin(alpha);
            verlist.emplace_back(x, y, z);
        }
    }
    verlist.emplace_back(0, 0, radius);
    verlist.emplace_back(0, 0, -radius);

    /// 2. Compute triangles of the sphere
    trilist.reserve(polarSamp * azimuSamp * 2);

    /// Top ring of triangles
    for (int j = 0; j < azimuSamp; j++) {
        trilist.emplace_back(midNum, j, (j + 1) % azimuSamp);
    }

    /// Middle rings of triangles
    for (int i = 1; i < polarSamp - 1; i++) {
        for (int j = 0; j < azimuSamp; j++) {
            int i1 = (i - 1) * azimuSamp + j;
            int j1 = (i - 1) * azimuSamp + (j + 1) % azimuSamp;
            int i2 = i * azimuSamp + j;
            int j2 = i * azimuSamp + (j + 1) % azimuSamp;
            trilist.emplace_back(i1, i2, j1);
            trilist.emplace_back(i2, j2, j1);
        }
    }

    /// Bottom ring of triangles
    for (int j = 0; j < azimuSamp; j++) {
        trilist.emplace_back(midNum + 1, midNum - azimuSamp + (j + 1) % azimuSamp, midNum - azimuSamp + j);
    }

    /// 3. Construct a triangular mesh of the sphere
    Mesh *mesh = new Mesh(verlist, trilist);
    return mesh;
}

Mesh *MeshCreator::CreateCone(const Eigen::Vector3d &baseCenter, const Eigen::Vector3d &apexPoint, double radius,
                              int radSamp) {
    /// 1. Create a cylinder with the given radius and computed length
    double length = (apexPoint - baseCenter).norm();
    Mesh *mesh = CreateCone(length, radius, radSamp);

    /// 2. Compute the translation matrix
    Eigen::Affine3d transMat = GetTranslationMatrix(baseCenter);

    /// 3. Compute the rotation matrix (note: default cylinder is aligned with x-axis)
    Eigen::Vector3d xAxis = {1, 0, 0};
    Eigen::Vector3d axis_n = (apexPoint - baseCenter).normalized();
    Eigen::Affine3d rotMat = GetRotationMatrix(xAxis, axis_n);

    /// 4. Transform the cylinder to its target position and orientation
    mesh->Transform(transMat * rotMat);
    return mesh;
}

Mesh *MeshCreator::CreateCone(double length, double radius, int radSamp) {
    /// Create a cone that is oriented along the +x-axis; its base is centered at the origin
    std::vector<Eigen::Vector3d> verlist;
    std::vector<Eigen::Vector3i> trilist;

    /// 1. Compute vertices of the cone
    verlist.reserve(radSamp + 2);

    /// Sampled points on the base
    for (int i = 0; i < radSamp; i++) {
        double beta = i * 2.0 * M_PI / radSamp;
        double x = 0;
        double y = radius * cos(beta);
        double z = radius * sin(beta);
        verlist.emplace_back(x, y, z);
    }
    /// Base center point
    verlist.emplace_back(0, 0, 0);
    /// Apex point
    verlist.emplace_back(length, 0, 0);

    /// 2. Compute triangles of the cone
    trilist.reserve(2 * radSamp);
    /// Triangles of the base
    for (int j = 0; j < radSamp; j++) {
        trilist.emplace_back(radSamp, (j + 1) % radSamp, j);
        trilist.emplace_back(radSamp + 1, j, (j + 1) % radSamp);
    }

    /// 3. Construct a triangular mesh of the cylinder
    Mesh *mesh = new Mesh(verlist, trilist);
    return mesh;
}