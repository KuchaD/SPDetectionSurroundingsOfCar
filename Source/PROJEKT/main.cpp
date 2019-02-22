// The contents of this file are in the public domain. See LICENSE_FOR_EXAMPLE_PROGRAMS.txt


/*
    This is an example illustrating the use of the timer object from the dlib C++ Library.

    The timer is an object that calls some user specified member function at regular
    intervals from another thread.
*/




#include <opencv2/opencv.hpp>
#include <iostream>
#include <dlib/dnn.h>
#include <dlib/image_io.h>
#include <dlib/image_processing.h>
#include <dlib/opencv.h>
using namespace std;
using namespace dlib;


int main()
{
    array2d<rgb_pixel> img;
    load_image(img, "../57075-pes.jpg");
    save_jpeg(img,"test.png",1);

    cv::Mat lMat= cv::imread("../57075-pes.jpg");
            cv::imwrite("testopen.png",lMat);

    return 0;
}

// ----------------------------------------------------------------------------------------

