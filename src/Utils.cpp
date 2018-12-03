#ifndef Utils_HEADER
#define Utils_HEADER


#include "Utils.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <dlib/opencv.h>
#include "opencv2/opencv.hpp"
#include <iostream>
#include <dlib/dnn.h>
#include <dlib/image_io.h>
#include <dlib/image_processing.h>

using namespace std;
using namespace cv;

namespace Utils
{
    Rect DlibOpenCV::dlibRectangleToOpenCV(dlib::rectangle r)
    {
    return Rect(Point2i(r.left(), r.top()), Point2i(r.right() + 1, r.bottom() + 1));
    }
}


#endif // DLIB_SVm_HEADER
