#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utility.hpp>

using namespace cv;

struct input_images{
    Mat my_part;
    int x;
    int y;
}; 

struct output_images{
    Mat my_part;
    int x;
    int y;
};

bool compareOrder(output_images i1, output_images i2);