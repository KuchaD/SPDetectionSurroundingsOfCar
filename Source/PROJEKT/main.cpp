// The contents of this file are in the public domain. See LICENSE_FOR_EXAMPLE_PROGRAMS.txt


/*
    This is an example illustrating the use of the timer object from the dlib C++ Library.

    The timer is an object that calls some user specified member function at regular
    intervals from another thread.
*/

/*
#include <iostream>
#include "dlib/image_processing.h"
#include <dlib/opencv.h>
#include "src/Network.h"
#include <dlib/dnn.h>

using namespace std;
using namespace dlib;



// ----------------------------------------------------------------------------------------

int main() try
{
    Network::Network lNet;

    lNet.Train();
    //lNet.LoadFromFile("/home/davelinux/Dokumenty/GIT/PROJEKT/dlib_rear_end_vehicles/mmod_rear_end_vehicle_detector.dat");

//    cv::Mat lImage = cv::imread("/home/davelinux/Dokumenty/GIT/PROJEKT/011551-R.jpg",cv::IMREAD_ANYCOLOR);
    //  lNet.ClassificationImage(lImage);
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


*/
// The contents of this file are in the public domain. See LICENSE_FOR_EXAMPLE_PROGRAMS.txt
/*
    This example shows how to train a CNN based object detector using dlib's
    loss_mmod loss layer.  This loss layer implements the Max-Margin Object
    Detection loss as described in the paper:
        Max-Margin Object Detection by Davis E. King (http://arxiv.org/abs/1502.00046).
    This is the same loss used by the popular SVM+HOG object detector in dlib
    (see fhog_object_detector_ex.cpp) except here we replace the HOG features
    with a CNN and train the entire detector end-to-end.  This allows us to make
    much more powerful detectors.

    It would be a good idea to become familiar with dlib's DNN tooling before reading this
    example.  So you should read dnn_introduction_ex.cpp and dnn_introduction2_ex.cpp
    before reading this example program.  You should also read the introductory DNN+MMOD
    example dnn_mmod_ex.cpp as well before proceeding.


    This example is essentially a more complex version of dnn_mmod_ex.cpp.  In it we train
    a detector that finds the rear ends of motor vehicles.  I will also discuss some
    aspects of data preparation useful when training this kind of detector.

*/
// Inception layer has some different convolutions inside.  Here we define
// blocks as convolutions with different kernel size that we will use in
// inception layer block.

#include <dlib/dnn.h>
#include <iostream>
#include <dlib/data_io.h>
#include "src/Network.h"
#include <dlib/opencv.h>
//#include "opencv2/opencv.hpp"

using namespace std;
using namespace dlib;





// ----------------------------------------------------------------------------------------

int main(int argc, char** argv) try
{
   // cv::Mat lMat = cv::imread("../011551-R.jpg",cv::IMREAD_ANYCOLOR);

    Network::Network lNet;
    //lNet.LoadFromFile("../mmod_rear_end_vehicle_detector.dat");
    //lNet.ClassificationImage(lMat);

    lNet.Train();
    return 0;

}
catch(std::exception& e)
{
    cout << e.what() << endl;
}






