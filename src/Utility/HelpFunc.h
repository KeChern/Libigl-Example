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

#ifndef HELPFUNC_H
#define HELPFUNC_H

#include <cfloat>
#include <Eigen/Geometry>

Eigen::Affine3d GetTranslationMatrix(const Eigen::Vector3d &transVec);
Eigen::Affine3d GetRotationMatrix(const double &rotAngle, const Eigen::Vector3d &rotAxis);
Eigen::Affine3d GetRotationMatrix(const double &rotAngle, const Eigen::Vector3d &rotAxis, const Eigen::Vector3d &rotCenter);
Eigen::Affine3d GetRotationMatrix(const Eigen::Vector3d &startVec, const Eigen::Vector3d &endVec);

Eigen::Affine3d GetScalingMatrix(const Eigen::Vector3d &scaleVec);
Eigen::Vector3d MultiplyPoint(const Eigen::Affine3d& mat,const Eigen::Vector3d &point);
Eigen::Vector3d MultiplyVector(const Eigen::Affine3d& mat,const Eigen::Vector3d &vec);


#endif //HELPFUNC_H
