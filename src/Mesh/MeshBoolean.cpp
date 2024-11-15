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
    igl::copyleft::cgal::mesh_boolean(meshA->VerM, meshA->FaceM, meshB->VerM, meshB->FaceM,
                                      igl::MESH_BOOLEAN_TYPE_UNION, V, F);
    Mesh *mesh = new Mesh(V, F);
    return mesh;
}

Mesh *MeshBoolean::MeshIntersect(Mesh *meshA, Mesh *meshB) {
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;
    igl::copyleft::cgal::mesh_boolean(meshA->VerM, meshA->FaceM, meshB->VerM, meshB->FaceM,
                                      igl::MESH_BOOLEAN_TYPE_INTERSECT, V, F);
    Mesh *mesh = new Mesh(V, F);
    return mesh;
}

Mesh *MeshBoolean::MeshMinus(Mesh *meshA, Mesh *meshB) {
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;
    igl::copyleft::cgal::mesh_boolean(meshA->VerM, meshA->FaceM, meshB->VerM, meshB->FaceM,
                                      igl::MESH_BOOLEAN_TYPE_MINUS, V, F);
    Mesh *mesh = new Mesh(V, F);
    return mesh;
}

Mesh *MeshBoolean::MeshXOR(Mesh *meshA, Mesh *meshB) {
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;
    igl::copyleft::cgal::mesh_boolean(meshA->VerM, meshA->FaceM, meshB->VerM, meshB->FaceM,
                                      igl::MESH_BOOLEAN_TYPE_XOR, V, F);
    Mesh *mesh = new Mesh(V, F);
    return mesh;
}

Mesh *MeshBoolean::MeshResolve(Mesh *meshA, Mesh *meshB) {
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;
    igl::copyleft::cgal::mesh_boolean(meshA->VerM, meshA->FaceM, meshB->VerM, meshB->FaceM,
                                      igl::MESH_BOOLEAN_TYPE_RESOLVE, V, F);
    Mesh *mesh = new Mesh(V, F);
    return mesh;
}

Mesh *MeshBoolean::MeshConnect(Mesh *meshA, Mesh *meshB) {
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;

    long numVerA, numVerB, numFaceA, numFaceB;
    numVerA = meshA->VerM.rows();
    numVerB = meshB->VerM.rows();
    numFaceA = meshA->FaceM.rows();
    numFaceB = meshB->FaceM.rows();

    V.resize(numVerA + numVerB, 3);
    F.resize(numFaceA + numFaceB, 3);

    V.block(0, 0, numVerA, 3) = meshA->VerM;
    F.block(0, 0, numFaceA, 3) = meshA->FaceM;

    V.block(numVerA, 0, numVerB, 3) = meshB->VerM;
    F.block(numFaceA, 0, numFaceB, 3) = meshB->FaceM.array() + numVerA;

    Mesh *mesh = new Mesh(V, F);
    return mesh;
}

Mesh *MeshBoolean::MeshConnect(const std::vector<Mesh *> &meshlist) {
    if (meshlist.empty()) {
        std::cout << " meshlist is Empty in 'MeshConnect' !" << std::endl;
    }
    Mesh *mesh;
    mesh = meshlist[0];
    for (Mesh *m: meshlist) {
        mesh = MeshConnect(mesh, m);
    }
    return mesh;
}