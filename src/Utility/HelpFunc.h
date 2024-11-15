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
#include <random>
#include <iostream>
#include <unordered_map>
#include <Eigen/Geometry>


double GetRandomDouble(double a, double b);

Eigen::Affine3d GetTranslationMatrix(const Eigen::Vector3d &transVec);
Eigen::Affine3d GetTranslationMatrix(double x, double y, double z);
Eigen::Affine3d GetRotationMatrix(const double &rotAngle, const Eigen::Vector3d &rotAxis);
Eigen::Affine3d GetRotationMatrix(const double &rotAngle, const Eigen::Vector3d &rotAxis, const Eigen::Vector3d &rotCenter);
Eigen::Affine3d GetRotationMatrix(const Eigen::Vector3d &startVec, const Eigen::Vector3d &endVec);
Eigen::Affine3d GetScalingMatrix(const Eigen::Vector3d &scaleVec);
Eigen::Affine3d GetScalingMatrix(double scale);

Eigen::Vector3d MultiplyPoint(const Eigen::Affine3d& mat,const Eigen::Vector3d &point);
Eigen::Vector3d MultiplyVector(const Eigen::Affine3d& mat,const Eigen::Vector3d &vec);

Eigen::RowVector3d GetRGB(const std::string& colorName);

#endif //HELPFUNC_H
