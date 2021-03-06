//
// Created by davelinux on 23.2.19.
//
#include "Network.h"

#include <dlib/opencv.h>
#include "../utils/Utils.h"
#include <iostream>
#include <dlib/dnn.h>
#include <dlib/image_io.h>
#include <dlib/image_processing.h>
#include <dlib/data_io.h>
#include <ctime>
#include "opencv2/opencv.hpp"


using namespace std;
using namespace cv;
using namespace dlib;

namespace Network
{
    Network::~Network(void){}

    void Network::LoadFromFile(std::string aFilePath)
    {

        deserialize(aFilePath) >> net;

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


            dlib::rectangle rect = d.rect;




            cv::Point lPos = cv::Point(rect.left(),rect.top());
            cv::rectangle(Image,Utils::DlibOpenCV::dlibRectangleToOpenCV(rect),cv::Scalar(255,0,0));
            cv::putText(Image, d.label,lPos,4,2,cv::Scalar(255,255,255));
        }

        cv::imwrite("test22.jpg",Image);


    }

    int Network::ignore_overlapped_boxes(std::vector<mmod_rect> &boxes, const test_box_overlap &overlaps) {
        int num_ignored = 0;
        for (size_t i = 0; i < boxes.size(); ++i)
        {
            if (boxes[i].ignore)
                continue;
            for (size_t j = i+1; j < boxes.size(); ++j)
            {
                if (boxes[j].ignore)
                    continue;
                if (overlaps(boxes[i], boxes[j]))
                {
                    ++num_ignored;
                    if(boxes[i].rect.area() < boxes[j].rect.area())
                        boxes[i].ignore = true;
                    else
                        boxes[j].ignore = true;
                }
            }
        }
        return num_ignored;
    }

    void Network::Train() {

        const std::string data_directory = "../dlib_rear_end_vehicles";


        std::vector<matrix<rgb_pixel>> images_train, images_test;
        std::vector<std::vector<mmod_rect>> boxes_train, boxes_test;
        load_image_dataset(images_train, boxes_train, data_directory+"/training.xml");
        load_image_dataset(images_test,  boxes_test,  data_directory+"/testing.xml");
        auto start = std::chrono::system_clock::now();
        auto start_t = chrono::system_clock::to_time_t(start);
        cout << "Start time: " << ctime(&start_t)<< endl;

        //Poznamky
        /*
         Negativni trenovaci data oznacena jako ignore.
         Kazde auto musi mit popisek

         Boxy mensi nez 35x35 pixel jsou ignorovany kvuli velikosti.
         Tak samo pokud jsou boxy pres sebe.


         Jak to funguje.
         Prochazi obrazak plavoucim oknem a pta se jestli je auto tady?

         */

        // To explain this non-max suppression idea further it's important to understand how
        // the detector works.  Essentially, sliding window detectors scan all image locations
        // and ask "is there a car here?".  If there really is a car in a specific location in
        // an image then usually many slightly different sliding window locations will produce
        // high detection scores, indicating that there is a car at those locations.  If we
        // just stopped there then each car would produce multiple detections.  But that isn't
        // what we want.  We want each car to produce just one detection.  So it's common for
        // detectors to include "non-maximum suppression" logic which simply takes the
        // strongest detection and then deletes all detections "close to" the strongest.  This
        // is a simple post-processing step that can eliminate duplicate detections.  However,
        // we have to define what "close to" means.  We can do this by looking at your training
        // data and checking how close the closest target boxes are to each other, and then
        // picking a "close to" measure that doesn't suppress those target boxes but is
        // otherwise as tight as possible.  This is exactly what the mmod_options object does
        // by default.
        //
        // Importantly, this means that if your training dataset contains an image with two
        // target boxes that really overlap a whole lot, then the non-maximum suppression
        // "close to" measure will be configured to allow detections to really overlap a whole
        // lot.  On the other hand, if your dataset didn't contain any overlapped boxes at all,
        // then the non-max suppression logic would be configured to filter out any boxes that
        // overlapped at all, and thus would be performing a much stronger non-max suppression.
        //
        // Why does this matter?  Well, remember that we want to avoid duplicate detections.
        // If non-max suppression just kills everything in a really wide area around a car then
        // the CNN doesn't really need to learn anything about avoiding duplicate detections.
        // However, if non-max suppression only suppresses a tiny area around each detection
        // then the CNN will need to learn to output small detection scores for those areas of
        // the image not suppressed.  The smaller the non-max suppression region the more the
        // CNN has to learn and the more difficult the learning problem will become.  This is
        // why we remove highly overlapped objects from the training dataset.  That is, we do
        // it so the non-max suppression logic will be able to be reasonably effective.  Here
        // we are ensuring that any boxes that are entirely contained by another are
        // suppressed.  We also ensure that boxes with an intersection over union of 0.5 or
        // greater are suppressed.  This will improve the resulting detector since it will be
        // able to use more aggressive non-max suppression settings.

        int num_overlapped_ignored_test = 0;
        for (auto& v : boxes_test)
            num_overlapped_ignored_test += ignore_overlapped_boxes(v, test_box_overlap(0.50, 0.95));

        int num_overlapped_ignored = 0;
        int num_additional_ignored = 0;
        for (auto& v : boxes_train)
        {
            num_overlapped_ignored += ignore_overlapped_boxes(v, test_box_overlap(0.50, 0.95));
            for (auto& bb : v)
            {
                if (bb.rect.width() < 35 && bb.rect.height() < 35)
                {
                    if (!bb.ignore)
                    {
                        bb.ignore = true;
                        ++num_additional_ignored;
                    }
                }

            }
        }

        // When modifying a dataset like this, it's a really good idea to print a log of how
        // many boxes you ignored.  It's easy to accidentally ignore a huge block of data, so
        // you should always look and see that things are doing what you expect.
        cout << "num_overlapped_ignored: "<< num_overlapped_ignored << endl;
        cout << "num_additional_ignored: "<< num_additional_ignored << endl;
        cout << "num_overlapped_ignored_test: "<< num_overlapped_ignored_test << endl;


        cout << "num training images: " << images_train.size() << endl;
        cout << "num testing images: " << images_test.size() << endl;


        // Our vehicle detection dataset has basically 3 different types of boxes.  Square
        // boxes, tall and skinny boxes (e.g. semi trucks), and short and wide boxes (e.g.
        // sedans).  Here we are telling the MMOD algorithm that a vehicle is recognizable as
        // long as the longest box side is at least 70 pixels long and the shortest box side is
        // at least 30 pixels long.  mmod_options will use these parameters to decide how large
        // each of the sliding windows needs to be so as to be able to detect all the vehicles.
        // Since our dataset has basically these 3 different aspect ratios, it will decide to
        // use 3 different sliding windows.  This means the final con layer in the network will
        // have 3 filters, one for each of these aspect ratios.
        //
        // Another thing to consider when setting the sliding window size is the "stride" of
        // your network.  The network we defined above downsamples the image by a factor of 8x
        // in the first few layers.  So when the sliding windows are scanning the image, they
        // are stepping over it with a stride of 8 pixels.  If you set the sliding window size
        // too small then the stride will become an issue.  For instance, if you set the
        // sliding window size to 4 pixels, then it means a 4x4 window will be moved by 8
        // pixels at a time when scanning. This is obviously a problem since 75% of the image
        // won't even be visited by the sliding window.  So you need to set the window size to
        // be big enough relative to the stride of your network.  In our case, the windows are
        // at least 30 pixels in length, so being moved by 8 pixel steps is fine.
        mmod_options options(boxes_train, 70, 30);


        // This setting is very important and dataset specific.  The vehicle detection dataset
        // contains boxes that are marked as "ignore", as we discussed above.  Some of them are
        // ignored because we set ignore to true in the above code.  However, the xml files
        // also contained a lot of ignore boxes.  Some of them are large boxes that encompass
        // large parts of an image and the intention is to have everything inside those boxes
        // be ignored.  Therefore, we need to tell the MMOD algorithm to do that, which we do
        // by setting options.overlaps_ignore appropriately.
        //
        // But first, we need to understand exactly what this option does.  The MMOD loss
        // is essentially counting the number of false alarms + missed detections produced by
        // the detector for each image.  During training, the code is running the detector on
        // each image in a mini-batch and looking at its output and counting the number of
        // mistakes.  The optimizer tries to find parameters settings that minimize the number
        // of detector mistakes.
        //
        // This overlaps_ignore option allows you to tell the loss that some outputs from the
        // detector should be totally ignored, as if they never happened.  In particular, if a
        // detection overlaps a box in the training data with ignore==true then that detection
        // is ignored.  This overlap is determined by calling
        // options.overlaps_ignore(the_detection, the_ignored_training_box).  If it returns
        // true then that detection is ignored.
        //
        // You should read the documentation for test_box_overlap, the class type for
        // overlaps_ignore for full details.  However, the gist is that the default behavior is
        // to only consider boxes as overlapping if their intersection over union is > 0.5.
        // However, the dlib vehicle detection dataset contains large boxes that are meant to
        // mask out large areas of an image.  So intersection over union isn't an appropriate
        // way to measure "overlaps with box" in this case.  We want any box that is contained
        // inside one of these big regions to be ignored, even if the detection box is really
        // small.  So we set overlaps_ignore to behave that way with this line.
        options.overlaps_ignore = test_box_overlap(0.5, 0.95);

        net_type net(options);

        // The final layer of the network must be a con layer that contains
        // options.detector_windows.size() filters.  This is because these final filters are
        // what perform the final "sliding window" detection in the network.  For the dlib
        // vehicle dataset, there will be 3 sliding window detectors, so we will be setting
        // num_filters to 3 here.

        net.subnet().layer_details().set_num_filters(options.detector_windows.size());


        dnn_trainer<net_type> trainer(net,sgd(0.0001,0.9));
        trainer.set_learning_rate(0.1);
        trainer.be_verbose();


        // While training, we are going to use early stopping.  That is, we will be checking
        // how good the detector is performing on our test data and when it stops getting
        // better on the test data we will drop the learning rate.  We will keep doing that
        // until the learning rate is less than 1e-4.   These two settings tell the trainer to
        // do that.  Essentially, we are setting the first argument to infinity, and only the
        // test iterations without progress threshold will matter.  In particular, it says that
        // once we observe 1000 testing mini-batches where the test loss clearly isn't
        // decreasing we will lower the learning rate.
        trainer.set_iterations_without_progress_threshold(50000);
        trainer.set_test_iterations_without_progress_threshold(1000);

        const string sync_filename = "mmod_cars_sync";
        trainer.set_synchronization_file(sync_filename, std::chrono::minutes(5));




        std::vector<matrix<rgb_pixel>> mini_batch_samples;
        std::vector<std::vector<mmod_rect>> mini_batch_labels;
        random_cropper cropper;
        cropper.set_seed(time(0));
        cropper.set_chip_dims(100, 100);
        // Usually you want to give the cropper whatever min sizes you passed to the
        // mmod_options constructor, or very slightly smaller sizes, which is what we do here.
        cropper.set_min_object_size(69,28);
        cropper.set_max_rotation_degrees(2);
        dlib::rand rnd;

        // Log the training parameters to the console
        cout << trainer << cropper << endl;

        int cnt = 1;
        // Run the trainer until the learning rate gets small.
        while(trainer.get_learning_rate() >= 1e-4)
        {
            // Every 30 mini-batches we do a testing mini-batch.
            if (cnt%30 != 0 || images_test.size() == 0)
            {
                cropper(10, images_train, boxes_train, mini_batch_samples, mini_batch_labels);
                // We can also randomly jitter the colors and that often helps a detector
                // generalize better to new images.
                for (auto&& img : mini_batch_samples)
                    disturb_colors(img, rnd);

                // It's a good idea to, at least once, put code here that displays the images
                // and boxes the random cropper is generating.  You should look at them and
                // think about if the output makes sense for your problem.  Most of the time
                // it will be fine, but sometimes you will realize that the pattern of cropping
                // isn't really appropriate for your problem and you will need to make some
                // change to how the mini-batches are being generated.  Maybe you will tweak
                // some of the cropper's settings, or write your own entirely separate code to
                // create mini-batches.  But either way, if you don't look you will never know.
                // An easy way to do this is to create a dlib::image_window to display the
                // images and boxes.

                trainer.train_one_step(mini_batch_samples, mini_batch_labels);
            }
            else
            {
                cropper(10, images_test, boxes_test, mini_batch_samples, mini_batch_labels);
                // We can also randomly jitter the colors and that often helps a detector
                // generalize better to new images.
                for (auto&& img : mini_batch_samples)
                    disturb_colors(img, rnd);

                trainer.test_one_step(mini_batch_samples, mini_batch_labels);
            }
            ++cnt;
        }
        // wait for training threads to stop
        trainer.get_net();
        cout << "done training" << endl;

        // Save the network to disk
        net.clean();
        serialize("mmod_rear_end_vehicle_detector.dat") << net;


        // It's a really good idea to print the training parameters.  This is because you will
        // invariably be running multiple rounds of training and should be logging the output
        // to a file.  This print statement will include many of the training parameters in
        // your log.
        cout << trainer << cropper << endl;

        cout << "\nsync_filename: " << sync_filename << endl;
        cout << "num training images: "<< images_train.size() << endl;
        cout << "training results: " << test_object_detection_function(net, images_train, boxes_train, test_box_overlap(), 0, options.overlaps_ignore);
        // Upsampling the data will allow the detector to find smaller cars.  Recall that
        // we configured it to use a sliding window nominally 70 pixels in size.  So upsampling
        // here will let it find things nominally 35 pixels in size.  Although we include a
        // limit of 1800*1800 here which means "don't upsample an image if it's already larger
        // than 1800*1800".  We do this so we don't run out of RAM, which is a concern because
        // some of the images in the dlib vehicle dataset are really high resolution.
        upsample_image_dataset<pyramid_down<2>>(images_train, boxes_train, 1800*1800);
        cout << "training upsampled results: " << test_object_detection_function(net, images_train, boxes_train, test_box_overlap(), 0, options.overlaps_ignore);


        cout << "num testing images: "<< images_test.size() << endl;
        cout << "testing results: " << test_object_detection_function(net, images_test, boxes_test, test_box_overlap(), 0, options.overlaps_ignore);
        upsample_image_dataset<pyramid_down<2>>(images_test, boxes_test, 1800*1800);
        cout << "testing upsampled results: " << test_object_detection_function(net, images_test, boxes_test, test_box_overlap(), 0, options.overlaps_ignore);

        /*
            This program takes many hours to execute on a high end GPU.  It took about a day to
            train on a NVIDIA 1080ti.  The resulting model file is available at
                http://dlib.net/files/mmod_rear_end_vehicle_detector.dat.bz2
            It should be noted that this file on dlib.net has a dlib::shape_predictor appended
            onto the end of it (see dnn_mmod_find_cars_ex.cpp for an example of its use).  This
            explains why the model file on dlib.net is larger than the
            mmod_rear_end_vehicle_detector.dat output by this program.

            You can see some videos of this vehicle detector running on YouTube:
                https://www.youtube.com/watch?v=4B3bzmxMAZU
                https://www.youtube.com/watch?v=bP2SUo5vSlc

            Also, the training and testing accuracies were:
                num training images: 2217
                training results: 0.990738 0.736431 0.736073
                training upsampled results: 0.986837 0.937694 0.936912
                num testing images: 135
                testing results: 0.988827 0.471372 0.470806
                testing upsampled results: 0.987879 0.651132 0.650399
        */
        auto end = std::chrono::system_clock::now();
        auto end_t = chrono::system_clock::to_time_t(start);
        std::chrono::duration<double> elapsed_seconds = end-start;
        cout << "End time: " << ctime(&end_t)<< endl;
        std::cout <<"Completa time in h "<< std::chrono::duration_cast<std::chrono::hours>(end-start).count()<< " hours\n";
        std::cout <<"Completa time in minutes "<< std::chrono::duration_cast<std::chrono::minutes>(end-start).count()<< " minutes\n";
        std::cout <<"Completa time in seconds "<< std::chrono::duration_cast<std::chrono::seconds>(end-start).count()<< " s\n";
    }


}
