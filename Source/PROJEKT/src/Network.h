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


    template <long num_filters, typename SUBNET> using level = relu<bn_con<con<num_filters,5,5,2,2,relu<bn_con<con<num_filters,5,5,1,1,SUBNET>>>>>>;

    template <typename SUBNET> using block_b1 = relu<con<4,1,1,1,1,SUBNET>>;
    template <typename SUBNET> using block_b2 = relu<con<4,3,3,1,1,SUBNET>>;
    template <typename SUBNET> using block_b3 = relu<con<4,1,1,1,1,max_pool<3,3,1,1,SUBNET>>>;
    template <typename SUBNET> using incept_b = inception3<block_b1,block_b2,block_b3,SUBNET>;

    using net_type = loss_mmod<level<32,incept_b<input_rgb_image_pyramid<pyramid_down<6>>>>>;


    class Network
    {
    private:
        net_type net;
        shape_predictor sp;

    public:
        ~Network(void);
        void LoadFromFile(std::string aFilePath);
        //void ClassificationImage(cv::Mat Image);
        void Train();
        int ignore_overlapped_boxes(std::vector<mmod_rect>& boxes,const test_box_overlap& overlaps);

    };
}


#endif //PROJEKT_NETWORK_H
