/// ========================================
///
///     HelpFunc.h
///
///     Common Functions
///
///     by Yingjie Cheng
///
///     2015-09-02
///
/// ========================================

#include "HelpFunc.h"

Eigen::Affine3d GetTranslationMatrix(const Eigen::Vector3d &transVec) {
    Eigen::Affine3d affineMat = Eigen::Affine3d::Identity();
    affineMat.translation() = transVec;
    return affineMat;
}

Eigen::Affine3d GetScalingMatrix(const Eigen::Vector3d &scaleVec){
    Eigen::Affine3d affineMat = Eigen::Affine3d::Identity();
    affineMat.scale(scaleVec);
    return affineMat;
}

Eigen::Vector3d MultiplyPoint(const Eigen::Affine3d &mat, const Eigen::Vector3d &point) {
    return mat * point;
}

Eigen::Vector3d MultiplyVector(const Eigen::Affine3d &mat, const Eigen::Vector3d &vec) {
    return mat.linear() * vec;
}