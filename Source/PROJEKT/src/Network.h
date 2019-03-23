//
// Created by davelinux on 23.2.19.
//

#ifndef PROJEKT_NETWORK_H
#define PROJEKT_NETWORK_H


#include <dlib/opencv.h>
#include <iostream>
#include <dlib/dnn.h>
#include <dlib/image_io.h>
#include <dlib/image_processing.h>
#include <iostream>
#include <dlib/dnn.h>
#include <dlib/image_io.h>
#include <dlib/image_processing.h>
#include <dlib/opencv.h>


namespace Network
{

    using namespace std;
    using namespace dlib;

    template <long num_filters, typename SUBNET> using con5d = con<num_filters,7,7,2,2,SUBNET>;
    template <long num_filters, typename SUBNET> using con5 = con <num_filters,7,7,1,1,SUBNET>;
    template <typename SUBNET> using downsampler  = relu<bn_con<con5d<32, relu<bn_con<con5d<32, relu<bn_con<con5d<16,SUBNET>>>>>>>>>;
    template <typename SUBNET> using rcon5  = relu<bn_con<con5<55,SUBNET>>>;
    using net_type = loss_mmod<con<1,9,9,1,1,rcon5<rcon5<rcon5<downsampler<input_rgb_image_pyramid<pyramid_down<6>>>>>>>>;



    class Network
    {
    private:
        net_type net;
        shape_predictor sp;

    public:
        ~Network(void);
        void LoadFromFile(std::string aFilePath);
        void ClassificationImage(cv::Mat Image);
        void Train();
        int ignore_overlapped_boxes(std::vector<mmod_rect>& boxes,const test_box_overlap& overlaps);

    };
}


#endif //PROJEKT_NETWORK_H
