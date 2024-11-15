/// ========================================
///
///     HelpFunc.cpp
///
///     Common Functions
///
///     by Yingjie Cheng
///
///     2015-09-02
///
/// ========================================

#include "HelpFunc.h"

double GetRandomDouble(double a, double b) {
    static std::mt19937 gen(rand());
    std::uniform_real_distribution<double> distribution(a, b);
    return distribution(gen);
}

Eigen::Affine3d GetTranslationMatrix(double x, double y, double z) {
    Eigen::Affine3d affineMat = Eigen::Affine3d::Identity();
    affineMat.translation() = Eigen::Vector3d(x, y, z);
    return affineMat;
}

Eigen::Affine3d GetTranslationMatrix(const Eigen::Vector3d &transVec) {
    Eigen::Affine3d affineMat = Eigen::Affine3d::Identity();
    affineMat.translation() = transVec;
    return affineMat;
}

Eigen::Affine3d GetRotationMatrix(const Eigen::Vector3d &rotAxis, const double &rotAngle) {
    Eigen::AngleAxisd angleAxis(rotAngle, rotAxis.normalized());
    Eigen::Matrix3d rotMat = angleAxis.toRotationMatrix();
    Eigen::Affine3d affineMat = Eigen::Affine3d::Identity();
    affineMat.linear() = rotMat;
    return affineMat;
}

Eigen::Affine3d
GetRotationMatrix(const Eigen::Vector3d &rotCenter, const Eigen::Vector3d &rotAxis, const double &rotAngle) {
    return GetTranslationMatrix(rotCenter) * GetRotationMatrix(rotAxis, rotAngle) * GetTranslationMatrix(-rotCenter);
}

Eigen::Affine3d GetRotationMatrix(const Eigen::Vector3d &startVec, const Eigen::Vector3d &endVec) {
    Eigen::Vector3d start_vec = startVec.normalized();
    Eigen::Vector3d end_vec = endVec.normalized();
    Eigen::Vector3d rotAxis = start_vec.cross(end_vec);

    Eigen::Affine3d rotMat;
    if (rotAxis.norm() < FLT_MIN) {
        if (start_vec.dot(end_vec) > 0.0f)
            rotMat.setIdentity();
        else {
            printf("WARNING: the 'startVec' aligns with the 'endVec' in the Function 'GetRotationMatrix' !!!\n");
            Eigen::Vector3d another_rotAxis = Eigen::Vector3d(0, -1, 0).cross(start_vec);
            if (another_rotAxis.norm() < FLT_MIN) {
                another_rotAxis = Eigen::Vector3d(0, 0, 1).cross(start_vec);
            }
            rotMat = GetRotationMatrix(another_rotAxis, M_PI);
        }
    } else {
        double angle = acos(start_vec.dot(end_vec));
        rotMat = GetRotationMatrix(rotAxis, angle);
    }
    return rotMat;
}


Eigen::Affine3d GetScalingMatrix(const Eigen::Vector3d &scaleVec) {
    Eigen::Affine3d affineMat = Eigen::Affine3d::Identity();
    affineMat.scale(scaleVec);
    return affineMat;
}

Eigen::Affine3d GetScalingMatrix(double scale) {
    return GetScalingMatrix(Eigen::Vector3d::Ones() * scale);
}

Eigen::Vector3d MultiplyPoint(const Eigen::Affine3d &mat, const Eigen::Vector3d &point) {
    return mat * point;
}

Eigen::Vector3d MultiplyVector(const Eigen::Affine3d &mat, const Eigen::Vector3d &vec) {
    return mat.linear() * vec;
}

Eigen::RowVector3d GetRGB(const std::string &colorName) {
    static const std::unordered_map<std::string, Eigen::Vector3d> colorMap = {
            {"red",          Eigen::RowVector3d(0.9, 0.4, 0.4)},
            {"orange",       Eigen::RowVector3d(0.9, 0.6, 0.4)},
            {"yellow",       Eigen::RowVector3d(0.9, 0.9, 0.5)},
            {"green",        Eigen::RowVector3d(0.4, 0.9, 0.4)},
            {"cyan",         Eigen::RowVector3d(0.4, 0.9, 0.9)},
            {"blue",         Eigen::RowVector3d(0.4, 0.4, 0.9)},
            {"purple",       Eigen::RowVector3d(0.7, 0.3, 0.9)},
            {"pink",         Eigen::RowVector3d(0.5, 0.2, 0.5)},
            {"blown",        Eigen::RowVector3d(0.4, 0.8, 0.7)},
            {"gray",         Eigen::RowVector3d(0.6, 0.6, 0.6)},

            {"light blue",   Eigen::RowVector3d(0.6, 0.6, 0.9)},
            {"light gray",   Eigen::RowVector3d(0.8, 0.8, 0.8)},
            {"light salmon", Eigen::RowVector3d(0.9, 0.6, 0.5)},

            {"dark purple",  Eigen::RowVector3d(0.0, 0.0, 0.0)},
            {"dark cyan",    Eigen::RowVector3d(0.0, 0.0, 0.0)},
            {"dark blue",    Eigen::RowVector3d(0.0, 0.0, 0.0)},
            {"dark yellow",  Eigen::RowVector3d(0.0, 0.0, 0.0)},

            {"black",        Eigen::RowVector3d(0.3, 0.4, 0.7)},
            {"white",        Eigen::RowVector3d(0.6, 0.6, 0.3)}
    };

    auto it = colorMap.find(colorName);
    if (it != colorMap.end()) {
        return it->second;
    } else {
        std::cout << "Unknown color name: " << colorName << std::endl;
        return {0.0, 0.0, 0.0};
    }
}