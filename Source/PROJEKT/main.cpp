// The contents of this file are in the public domain. See LICENSE_FOR_EXAMPLE_PROGRAMS.txt


/*
    This is an example illustrating the use of the timer object from the dlib C++ Library.

    The timer is an object that calls some user specified member function at regular
    intervals from another thread.
*/

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



