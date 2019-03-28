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


    template <typename SUBNET> using block_a1 = relu<con<10,1,1,1,1,SUBNET>>;
    template <typename SUBNET> using block_a2 = relu<con<10,3,3,1,1,relu<con<16,1,1,1,1,SUBNET>>>>;
    template <typename SUBNET> using block_a3 = relu<con<10,5,5,1,1,relu<con<16,1,1,1,1,SUBNET>>>>;
    template <typename SUBNET> using block_a4 = relu<con<10,1,1,1,1,max_pool<3,3,1,1,SUBNET>>>;

// Here is inception layer definition. It uses different blocks to process input
// and returns combined output.  Dlib includes a number of these inceptionN
// layer types which are themselves created using concat layers.
    template <typename SUBNET> using incept_a = inception4<block_a1,block_a2,block_a3,block_a4, SUBNET>;

// Network can have inception layers of different structure.  It will work
// properly so long as all the sub-blocks inside a particular inception block
// output tensors with the same number of rows and columns.
    template <typename SUBNET> using block_b1 = relu<con<4,1,1,1,1,SUBNET>>;
    template <typename SUBNET> using block_b2 = relu<con<4,3,3,1,1,SUBNET>>;
    template <typename SUBNET> using block_b3 = relu<con<4,1,1,1,1,max_pool<3,3,1,1,SUBNET>>>;
    template <typename SUBNET> using incept_b = inception3<block_b1,block_b2,block_b3,SUBNET>;

// Now we can define a simple network for classifying MNIST digits.  We will
// train and test this network in the code below.
    using net_type = loss_mmod<con<1,6,6,1,1,
                            max_pool<2,2,2,2,incept_b<
                                    max_pool<2,2,2,2,incept_a<
                                            input_rgb_image_pyramid<pyramid_down<6>>
                                    >>>>>>;



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
