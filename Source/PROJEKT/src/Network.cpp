//
// Created by davelinux on 23.2.19.
//
#include "Network.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <dlib/opencv.h>
#include "opencv2/opencv.hpp"
#include "../utils/Utils.h"
#include <iostream>
#include <dlib/dnn.h>
#include <dlib/image_io.h>
#include <dlib/image_processing.h>


using namespace std;
using namespace cv;
using namespace dlib;

namespace Network
{
    Network::~Network(void){}

    void Network::LoadFromFile(std::string aFilePath)
    {
        ///home/davelinux/Documents/SEMESTRALPROJECT/src/dlib_rear_end_vehicles/mmod_rear_end_vehicle_detector.dat
        deserialize(aFilePath) >> net >> sp;

    }
    void Network::ClassificationImage(cv::Mat Image)
    {

        cv_image<bgr_pixel> image(Image);
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
            dlib::rectangle rect;

            for (unsigned long j = 0; j < fd.num_parts(); ++j)
                rect += fd.part(j);


            //cv::Point lPos = cv::Point(rect.right,rect.top);
            cv::rectangle(Image,Utils::DlibOpenCV::dlibRectangleToOpenCV(rect),cv::Scalar(255,0,0));
            //cv::putText(Image, d.label,lPos,4,2,cv::Scalar(255,255,255));
        }

        cv::imwrite("/home/davelinux/Dokumenty/GIT/PROJEKT/test2.jpg",Image);

    }
}
