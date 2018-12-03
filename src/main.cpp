#define DLIB_JPEG_SUPPORT
#define DLIB_PNG_SUPPORT
// The contents of this file are in the public domain. See LICENSE_FOR_EXAMPLE_PROGRAMS.txt
/*
    This example shows how to run a CNN based vehicle detector using dlib.  The
    example loads a pretrained model and uses it to find the rear ends of cars in
    an image.  We will also visualize some of the detector's processing steps by
    plotting various intermediate images on the screen.  Viewing these can help
    you understand how the detector works.
    
    The model usDlibOpenCVed by this example was trained by the dnn_mmod_train_find_cars_ex.cpp 
    example.  Also, since this is a CNN, you really should use a GPU to get the
    best execution speed.  For instance, when run on a NVIDIA 1080ti, this detector 
    runs at 98fps when run on the provided test image.  That's more than an order 
    of magnitude faster than when run on the CPU.

    Users who are just learning about dlib's deep learning API should read
    the dnn_introduction_ex.cpp and dnn_introduction2_ex.cpp examples to learn
    how the API works.  For an introduction to the object detection method you
    should read dnn_mmod_ex.cpp.

    You can also see some videos of this vehicle detector running on YouTube:
        https://www.youtube.com/watch?v=4B3bzmxMAZU
        https://www.youtube.com/watch?v=bP2SUo5vSlc
*/


#include <iostream>
#include <dlib/dnn.h>
#include <dlib/image_io.h>
#include <dlib/image_processing.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <dlib/opencv.h>
#include "opencv2/opencv.hpp"
#include "Utils.h"

using namespace std;
using namespace dlib;




// The rear view vehicle detector network
template <long num_filters, typename SUBNET> using con5d = con<num_filters,5,5,2,2,SUBNET>;
template <long num_filters, typename SUBNET> using con5  = con<num_filters,5,5,1,1,SUBNET>;
template <typename SUBNET> using downsampler  = relu<affine<con5d<32, relu<affine<con5d<32, relu<affine<con5d<16,SUBNET>>>>>>>>>;
template <typename SUBNET> using rcon5  = relu<affine<con5<55,SUBNET>>>;
using net_type = loss_mmod<con<1,9,9,1,1,rcon5<rcon5<rcon5<downsampler<input_rgb_image_pyramid<pyramid_down<6>>>>>>>>;

// ----------------------------------------------------------------------------------------

int main() try
{
    net_type net;
    shape_predictor sp;
    // You can get this file from http://dlib.net/files/mmod_rear_end_vehicle_detector.dat.bz2
    // This network was produced by the dnn_mmod_train_find_cars_ex.cpp example program.
    // As you can see, the file also includes a separately trained shape_predictor.  To see
    // a generic example of how to train those refer to train_shape_predictor_ex.cpp.
    deserialize("/home/davelinux/Documents/SEMESTRALPROJECT/src/dlib_rear_end_vehicles/mmod_rear_end_vehicle_detector.dat") >> net >> sp;

    cv::Mat lImage = cv::imread("/home/davelinux/Documents/SEMESTRALPROJECT/src/dlib_rear_end_vehicles/997d-Parking-Residential-On-street.jpg");
    cv_image<bgr_pixel> image(lImage);
    matrix<rgb_pixel> img;
    assign_image(img, image);

//     // Run the detector on the image and show us the output.
    for (auto&& d : net(img))
    {
        // We use a shape_predictor to refine the exact shape and location of the detection
        // box.  This shape_predictor is trained to simply output the 4 corner points of
        // the box.  So all we do is make a rectangle that tightly contains those 4 points
        // and that rectangle is our refined detection position.
        auto fd =  sp(img,d);
        rectangle rect;
        
        for (unsigned long j = 0; j < fd.num_parts(); ++j)
            rect += fd.part(j);

        
        //cv::Point lPos = cv::Point(rect.right,rect.top);
        cv::rectangle(lImage,Utils::DlibOpenCV::dlibRectangleToOpenCV(rect),cv::Scalar(255,0,0));
        //cv::putText(lImage, d.label,lPos,4,2,cv::Scalar(255,255,255));
    }

cv::imwrite("/home/davelinux/Documents/SEMESTRALPROJECT/src/dlib_rear_end_vehicles/test2.jpg",lImage);

    //cv::waitKey(0); // wait until keypressed

	return 0;
}
catch(image_load_error& e)
{
    cout << e.what() << endl;
    cout << "The test image is located in the examples folder.  So you should run this program from a sub folder so that the relative path is correct." << endl;
}
catch(serialization_error& e)
{
    cout << e.what() << endl;
    cout << "The correct model file can be obtained from: http://dlib.net/files/mmod_rear_end_vehicle_detector.dat.bz2" << endl;
}
catch(std::exception& e)
{
    cout << e.what() << endl;
}




