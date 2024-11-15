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
    std::vector<Eigen::Vector3d> verList;
    std::vector<Eigen::Vector3i> faceList;

    /// 1. Compute vertices of the cuboid
    double minX = -0.5f * sizeVec[0];
    double minY = -0.5f * sizeVec[1];
    double minZ = -0.5f * sizeVec[2];

    double maxX = 0.5f * sizeVec[0];
    double maxY = 0.5f * sizeVec[1];
    double maxZ = 0.5f * sizeVec[2];

    verList.reserve(8);
    verList.emplace_back(minX, minY, maxZ);
    verList.emplace_back(maxX, minY, maxZ);
    verList.emplace_back(maxX, maxY, maxZ);
    verList.emplace_back(minX, maxY, maxZ);

    verList.emplace_back(minX, minY, minZ);
    verList.emplace_back(maxX, minY, minZ);
    verList.emplace_back(maxX, maxY, minZ);
    verList.emplace_back(minX, maxY, minZ);

    /// 2. Compute triangles of the cuboid
    faceList.reserve(12);
    faceList.emplace_back(5, 4, 7);
    faceList.emplace_back(5, 7, 6);
    faceList.emplace_back(7, 2, 6);
    faceList.emplace_back(7, 3, 2);

    faceList.emplace_back(1, 0, 4);
    faceList.emplace_back(1, 3, 0);
    faceList.emplace_back(5, 6, 2);
    faceList.emplace_back(5, 2, 1);

    faceList.emplace_back(4, 5, 1);
    faceList.emplace_back(1, 2, 3);
    faceList.emplace_back(0, 3, 4);
    faceList.emplace_back(4, 3, 7);

    /// 3. Construct a triangular mesh
    Mesh *mesh = new Mesh(verList, faceList);
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
    std::vector<Eigen::Vector3d> verList;
    std::vector<Eigen::Vector3i> faceList;

    /// 1. Computer vertices of the cylinder
    double halfLength = 0.5f * length;
    verList.reserve(2 * radSamp + 2);
    /// Sampled points on the right cap
    for (int i = 0; i < radSamp; i++) {
        double beta = i * 2.0 * M_PI / radSamp;

        double x = halfLength;
        double y = radius * cos(beta);
        double z = radius * sin(beta);

        verList.emplace_back(x, y, z);
    }
    /// Sampled points on the left cap
    for (int i = 0; i < radSamp; i++) {
        double beta = i * 2.0 * M_PI / radSamp;

        double x = -halfLength;
        double y = radius * cos(beta);
        double z = radius * sin(beta);

        verList.emplace_back(x, y, z);
    }
    /// Center point of the right cap
    verList.emplace_back(halfLength, 0, 0);
    /// Center point of the left cap
    verList.emplace_back(-halfLength, 0, 0);

    /// 2. Computer triangles of the cylinder
    faceList.reserve(radSamp * 4);
    for (int i = 0; i < radSamp; i++) {
        int i1 = i;
        int j1 = (i + 1) % radSamp;
        int i2 = i + radSamp;
        int j2 = j1 + radSamp;
        faceList.emplace_back(i1, j2, j1);
        faceList.emplace_back(i2, j2, i1);
        faceList.emplace_back(i1, j1, 2 * radSamp);
        faceList.emplace_back(j2, i2, 2 * radSamp + 1);
    }

    /// 3. Construct a triangular mesh of the cylinder
    Mesh *mesh = new Mesh(verList, faceList);
    return mesh;
}

Mesh *MeshCreator::CreateSphere(const Eigen::Vector3d &center, double radius, int radSamp) {
    Mesh *mesh = CreateSphere(radius, radSamp);
    mesh->Transform(GetTranslationMatrix(center));
    return mesh;
}

Mesh *MeshCreator::CreateSphere(double radius, int radSamp) {
    std::vector<Eigen::Vector3d> verList;
    std::vector<Eigen::Vector3i> faceList;

    int polarSamp = radSamp / 2;
    int azimuSamp = radSamp;

    /// 1. Compute vertices of the sphere
    int midNum = (polarSamp - 1) * azimuSamp;
    verList.reserve(midNum + 2);
    for (int i = 1; i < polarSamp; i++) {
        double alpha = M_PI_2 - M_PI * i / polarSamp;
        for (int j = 0; j < azimuSamp; j++) {
            double beta = j * 2.0 * M_PI / azimuSamp;
            double x = radius * cos(alpha) * cos(beta);
            double y = radius * cos(alpha) * sin(beta);
            double z = radius * sin(alpha);
            verList.emplace_back(x, y, z);
        }
    }
    verList.emplace_back(0, 0, radius);
    verList.emplace_back(0, 0, -radius);

    /// 2. Compute triangles of the sphere
    faceList.reserve(polarSamp * azimuSamp * 2);

    /// Top ring of triangles
    for (int j = 0; j < azimuSamp; j++) {
        faceList.emplace_back(midNum, j, (j + 1) % azimuSamp);
    }

    /// Middle rings of triangles
    for (int i = 1; i < polarSamp - 1; i++) {
        for (int j = 0; j < azimuSamp; j++) {
            int i1 = (i - 1) * azimuSamp + j;
            int j1 = (i - 1) * azimuSamp + (j + 1) % azimuSamp;
            int i2 = i * azimuSamp + j;
            int j2 = i * azimuSamp + (j + 1) % azimuSamp;
            faceList.emplace_back(i1, i2, j1);
            faceList.emplace_back(i2, j2, j1);
        }
    }

    /// Bottom ring of triangles
    for (int j = 0; j < azimuSamp; j++) {
        faceList.emplace_back(midNum + 1, midNum - azimuSamp + (j + 1) % azimuSamp, midNum - azimuSamp + j);
    }

    /// 3. Construct a triangular mesh of the sphere
    Mesh *mesh = new Mesh(verList, faceList);
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
    Eigen::Vector3d centerAxis = (apexPoint - baseCenter).normalized();
    Eigen::Affine3d rotMat = GetRotationMatrix(xAxis, centerAxis);

    /// 4. Transform the cylinder to its target position and orientation
    mesh->Transform(transMat * rotMat);
    return mesh;
}

Mesh *MeshCreator::CreateCone(double length, double radius, int radSamp) {
    /// Create a cone that is oriented along the +x-axis; its base is centered at the origin
    std::vector<Eigen::Vector3d> verList;
    std::vector<Eigen::Vector3i> faceList;

    /// 1. Compute vertices of the cone
    verList.reserve(radSamp + 2);

    /// Sampled points on the base
    for (int i = 0; i < radSamp; i++) {
        double beta = i * 2.0 * M_PI / radSamp;
        double x = 0;
        double y = radius * cos(beta);
        double z = radius * sin(beta);
        verList.emplace_back(x, y, z);
    }
    /// Base center point
    verList.emplace_back(0, 0, 0);
    /// Apex point
    verList.emplace_back(length, 0, 0);

    /// 2. Compute triangles of the cone
    faceList.reserve(2 * radSamp);
    /// Triangles of the base
    for (int j = 0; j < radSamp; j++) {
        faceList.emplace_back(radSamp, (j + 1) % radSamp, j);
        faceList.emplace_back(radSamp + 1, j, (j + 1) % radSamp);
    }

    /// 3. Construct a triangular mesh of the cylinder
    Mesh *mesh = new Mesh(verList, faceList);
    return mesh;
}

Mesh *MeshCreator::CreateRectangularSurface(const std::vector<Eigen::Vector3d> &verList, int rows, int cols) {
    if (verList.size() != rows * cols)
        std::cout << "rows * cols is NOT equal to size of vector!" << std::endl;

    if (rows < 2 || cols < 2)
        std::cout << "rows/cols is less than 2!" << std::endl;

    std::vector<Eigen::Vector3i> faceList;
    faceList.reserve((rows - 1) * (cols - 1));
    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < cols - 1; j++) {
            int id = i * cols + j;
            faceList.emplace_back(id, id + cols, id + 1);
            faceList.emplace_back(id + 1, id + cols, id + cols + 1);
        }
    }
    Mesh *mesh = new Mesh(verList, faceList);
    return mesh;
}

Mesh *MeshCreator::Create3DCurve(const std::vector<Eigen::Vector3d> &ptList, double radius, int radSamp,
                                 const std::string &type) {
    int ptNum = static_cast<int>(ptList.size());
    Eigen::Vector3d center = Eigen::Vector3d::Zero();
    for (const Eigen::Vector3d &pt: ptList) {
        center += pt;
    }
    center /= ptNum;

    std::vector<Eigen::Vector3d> tangentList(ptNum);
    for (int i = 0; i < ptNum - 1; i++) {
        int nexti = (i + 1) % ptNum;
        tangentList[i] = (ptList[nexti] - ptList[i]).normalized();
    }
    tangentList[ptNum - 1] = (ptList[ptNum - 1] - ptList[ptNum - 2]).normalized();

    std::vector<Eigen::Vector3d> normalList(ptNum), binormalList(ptNum);
    for (int i = 0; i < ptNum; i++) {
        Eigen::Vector3d normal = ptList[i] - center;
        normal = normal - normal.dot(tangentList[i]) * tangentList[i];
        normalList[i] = normal.normalized();

        Eigen::Vector3d binormal = tangentList[i].cross(normalList[i]);
        binormalList[i] = binormal.normalized();
    }

    std::vector<Eigen::Vector3d> verList;
    verList.reserve(ptNum * radSamp + 2);
    for (int i = 0; i < ptNum; i++) {
        for (int j = 0; j < radSamp; j++) {
            double theta = j * 2 * M_PI / radSamp;
            Eigen::Vector3d EnvPt = ptList[i] + radius * (normalList[i] * cos(theta) + binormalList[i] * sin(theta));
            verList.emplace_back(EnvPt);
        }
    }
    if (type == "open") {
        verList.emplace_back(ptList[0]);
        verList.emplace_back(ptList[ptNum - 1]);
    }

    std::vector<Eigen::Vector3d> faceList;
    int maxFaceNum;
    if (type == "closed")
        maxFaceNum = ptNum;
    else if (type == "open")
        maxFaceNum = ptNum - 1;
    else {
        maxFaceNum = -1;
        printf("Type in 'Create3DCurve' is invaild!");
    }

    faceList.reserve(maxFaceNum * radSamp + radSamp);
    for (int i = 0; i < maxFaceNum; i++) {
        for (int j = 0; j < radSamp; j++) {
            int i1 = i * radSamp;
            int i2 = (i1 + radSamp) % (ptNum * radSamp);
            int j1 = j;
            int j2 = (j + 1) % radSamp;
            faceList.emplace_back(i1 + j1, i2 + j2, i2 + j1);
            faceList.emplace_back(i1 + j1, i1 + j2, i2 + j2);
        }
    }

    if (type == "open") {
        for (int j = 0; j < radSamp; j++) {
            int i = ptNum * radSamp;
            int j1 = j;
            int j2 = (j + 1) % radSamp;
            faceList.emplace_back(i, j2, j1);

            i = (ptNum - 1) * radSamp;
            faceList.emplace_back(i, i + j1, i + j2);
        }
    }
}