/// ========================================
///
///     MeshBoolean.cpp
///
///     Mesh boolean operation
///
///     by Yingjie Cheng
///
///     2020-11-20
///
/// ========================================

#include "MeshBoolean.h"

Mesh *MeshBoolean::MeshUnion(Mesh *meshA, Mesh *meshB) {
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;
    igl::copyleft::cgal::mesh_boolean(meshA->verM, meshA->faceM, meshB->verM, meshB->faceM,
                                      igl::MESH_BOOLEAN_TYPE_UNION, V, F);
    Mesh *mesh = new Mesh(V, F);
    return mesh;
}

Mesh *MeshBoolean::MeshIntersect(Mesh *meshA, Mesh *meshB) {
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;
    igl::copyleft::cgal::mesh_boolean(meshA->verM, meshA->faceM, meshB->verM, meshB->faceM,
                                      igl::MESH_BOOLEAN_TYPE_INTERSECT, V, F);
    Mesh *mesh = new Mesh(V, F);
    return mesh;
}

Mesh *MeshBoolean::MeshMinus(Mesh *meshA, Mesh *meshB) {
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;
    igl::copyleft::cgal::mesh_boolean(meshA->verM, meshA->faceM, meshB->verM, meshB->faceM,
                                      igl::MESH_BOOLEAN_TYPE_MINUS, V, F);
    Mesh *mesh = new Mesh(V, F);
    return mesh;
}

Mesh *MeshBoolean::MeshXOR(Mesh *meshA, Mesh *meshB) {
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;
    igl::copyleft::cgal::mesh_boolean(meshA->verM, meshA->faceM, meshB->verM, meshB->faceM,
                                      igl::MESH_BOOLEAN_TYPE_XOR, V, F);
    Mesh *mesh = new Mesh(V, F);
    return mesh;
}

Mesh *MeshBoolean::MeshResolve(Mesh *meshA, Mesh *meshB) {
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;
    igl::copyleft::cgal::mesh_boolean(meshA->verM, meshA->faceM, meshB->verM, meshB->faceM,
                                      igl::MESH_BOOLEAN_TYPE_RESOLVE, V, F);
    Mesh *mesh = new Mesh(V, F);
    return mesh;
}

Mesh *MeshBoolean::MeshConnect(Mesh *meshA, Mesh *meshB) {
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;

    long numVerA, numVerB, numFaceA, numFaceB;
    numVerA = meshA->verM.rows();
    numVerB = meshB->verM.rows();
    numFaceA = meshA->faceM.rows();
    numFaceB = meshB->faceM.rows();

    V.resize(numVerA + numVerB, 3);
    F.resize(numFaceA + numFaceB, 3);

    V.block(0, 0, numVerA, 3) = meshA->verM;
    F.block(0, 0, numFaceA, 3) = meshA->faceM;

    V.block(numVerA, 0, numVerB, 3) = meshB->verM;
    F.block(numFaceA, 0, numFaceB, 3) = meshB->faceM.array() + numVerA;

    Mesh *mesh = new Mesh(V, F);
    return mesh;
}

Mesh *MeshBoolean::MeshConnect(const std::vector<Mesh *> &meshlist) {
    if (meshlist.size() == 0) {
        std::cout << " meshlist is Empty in 'MeshConnect' !" << std::endl;
    }
    Mesh *mesh;
    mesh = meshlist[0];
    for (Mesh *m: meshlist) {
        mesh = MeshConnect(mesh, m);
    }
    return mesh;
}