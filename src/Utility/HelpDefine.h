/// ========================================
///
///     HelpDefine.h
///
///     Common Parameter Settings
///
///     by Yingjie Cheng and Peng Song
///
///     2022-08-08
///
/// ========================================
#ifndef HELPDEFINE_H
#define HELPDEFINE_H

#ifndef ToRadian
#define ToRadian(angle)        (angle / 180.0 * M_PI)
#endif

#ifndef ToDegree
#define ToDegree(angle)        (angle * 180.0 / M_PI)
#endif

#ifndef MAX
#define MAX(a, b)        ( ((a) > (b)) ? (a) : (b) )
#endif

#ifndef MIN
#define MIN(a, b)        ( ((a) < (b)) ? (a) : (b) )
#endif

//#ifndef M_PI
//#define M_PI            3.1415926535897932384626433832795
//#endif

#endif //HELPDEFINE_H
