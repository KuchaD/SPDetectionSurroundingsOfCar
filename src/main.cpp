
#include <dlib/dnn.h>
#include <iostream>
#include <dlib/data_io.h>
#include <dlib/opencv.h>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace dlib;


int main(int argc, char** argv) 
{
    // cv::Mat src_img = cv::imread("/home/davelinux/Documents/SEMESTRALPROJECT/57075-pes.jpg",CV_LOAD_IMAGE_GRAYSCALE);  
   
    //  if(! src_img.data )                              // Check for invalid input
    // {
    //     cout <<  "Could not open or find the image" << std::endl ;
    //     return -1;
    // }
    // cv::imshow("test",src_img);
    // cv::waitKey(0);

  // from opencv to dlib
    // Mat mat_img = Mat::zeros(3, 3, CV_8UC(5));
    // cv_image<custom_pixel> dlib_img(mat_img);

    // //from dlib to opencv
    // Mat mat_img_new = dlib::toMat(dlib_img);

    std::vector<matrix<unsigned char>> training_images;
    std::vector<unsigned long>         training_labels;
    std::vector<matrix<unsigned char>> testing_images;
    std::vector<unsigned long>         testing_labels;
    load_mnist_dataset("/home/davelinux/Documents/SEMESTRALPROJECT/src/mnist", training_images, training_labels, testing_images, testing_labels);

    cv::Mat out = dlib::toMat(training_images.at(1));
    cv::imshow("test", out);

    cv::waitKey(0);
    return 0;
}

