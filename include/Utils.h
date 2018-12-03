
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <dlib/opencv.h>
#include "opencv2/opencv.hpp"
#include <iostream>
#include <dlib/dnn.h>
#include <dlib/image_io.h>
#include <dlib/image_processing.h>

namespace Utils
{
    class DlibOpenCV
    {
    public:
        static cv::Rect dlibRectangleToOpenCV(dlib::rectangle r);

    };
} 
