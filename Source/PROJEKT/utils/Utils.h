//
// Created by davelinux on 23.2.19.
//

#ifndef PROJEKT_UTILS_H
#define PROJEKT_UTILS_H

#include <dlib/geometry/rectangle.h>
#include <opencv2/core/types.hpp>

namespace Utils
{
    class DlibOpenCV
    {
    public:
        static cv::Rect dlibRectangleToOpenCV(dlib::rectangle r);

    };
}



#endif //PROJEKT_UTILS_H
