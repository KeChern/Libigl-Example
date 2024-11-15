/// ========================================
///
///     MeshBoolean.h
///
///     Mesh boolean operation
///
///     by Yingjie Cheng
///
///     2020-11-20
///
/// ========================================

#ifndef MESHBOOLEAN_H
#define MESHBOOLEAN_H

#include <igl/copyleft/cgal/mesh_boolean.h>

#include "Mesh/Mesh.h"

class MeshBoolean {
public:
    MeshBoolean() = default;
    ~MeshBoolean() = default;

    static Mesh *MeshUnion(Mesh *meshA, Mesh *meshB);
//    static Mesh *MeshIntersect(Mesh *meshA, Mesh *meshB);
//    static Mesh *MeshMinus(Mesh *meshA, Mesh *meshB);
//    static Mesh *MeshXOR(Mesh *meshA, Mesh *meshB);
//    static Mesh *MeshResolve(Mesh *meshA, Mesh *meshB);
//
//    static Mesh *MeshConnect(Mesh *meshA, Mesh *meshB);
//    static Mesh *MeshConnect(const std::vector<Mesh *> &meshlist);
};


#endif //MESHBOOLEAN_H
