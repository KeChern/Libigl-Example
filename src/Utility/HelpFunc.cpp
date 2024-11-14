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

Eigen::Affine3d GetRotationMatrix(const double &rotAngle, const Eigen::Vector3d &rotAxis) {
    Eigen::AngleAxisd angleAxis(rotAngle, rotAxis.normalized());
    Eigen::Matrix3d rotMat = angleAxis.toRotationMatrix();
    Eigen::Affine3d affineMat = Eigen::Affine3d::Identity();
    affineMat.linear() = rotMat;
    return affineMat;
}

Eigen::Affine3d GetRotationMatrix(const double &rotAngle, const Eigen::Vector3d &rotAxis, const Eigen::Vector3d &rotCenter) {
    return GetTranslationMatrix(rotCenter) * GetRotationMatrix(rotAngle, rotAxis) * GetTranslationMatrix(-rotCenter);
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
            rotMat = GetRotationMatrix(M_PI, another_rotAxis);
        }
    } else {
        double angle = acos(start_vec.dot(end_vec));
        rotMat = GetRotationMatrix(angle, rotAxis);
    }
    return rotMat;
}


Eigen::Affine3d GetScalingMatrix(const Eigen::Vector3d &scaleVec) {
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