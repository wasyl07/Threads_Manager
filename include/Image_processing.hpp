#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utility.hpp>

#include <vector>

using namespace cv;
using namespace std;

typedef vector<input_images>  divided_image;
typedef vector<output_images> processed_image;

divided_image divide_image(Mat source, int blocks);
divided_image Read_image(string file_name, int blocks);
Mat Process_Image(processed_image output);

divided_image Read_image(string file_name, int blocks)
{
    string image_path = samples::findFile("/home/adam/Projects/Threads_Manager/" + file_name);
    Mat img = imread(image_path, IMREAD_COLOR);
    divided_image divided_images = divide_image(img, blocks);
    return divided_images;
}

divided_image divide_image(Mat source, int blocks)
{
    divided_image divided_images;

    int w = 1;
    int k = blocks;
    bool Do_we_have_a_solution = false;
    while (Do_we_have_a_solution == false)
    {
        k = k / 2;
        w = w * 2;
        if (w == k)
        {
            w = w;
            k = k;
            Do_we_have_a_solution = true;
            break;
        }
        else if (k < 2)
        {
            k = (k * 2);
            w = w / 2;
            Do_we_have_a_solution = true;
            break;
        }
    }

    int image_rows = source.rows / w;
    int image_cols = source.cols / k;

    int order = 0;

    Point p(0, 0);
    int i = 0;
    for (float i = (((w / 2.0) * 2.0) - 1.0); i >= (((w / 2.0) * (-2.0) + 1.0)); i--)
    {
        if (i == 0)
        {
            i--;
        }
        for (int j = (((k / 2) * (-2) + 1)); j <= (((k / 2) * 2) - 1); j++)
        {
            if (j == 0)
            {
                j++;
            }
            Mat tmp = Mat(source, Rect(p.x, p.y, image_cols, image_rows));
            input_images *images = new input_images();
            images->my_part = tmp;
            images->order = order;
            divided_images.push_back(*images);
            p.x += image_cols;
            order++;
        }
        p.x = 0;
        p.y += image_cols;
    }
    return divided_images;
}
Mat Process_Image(processed_image output)
{
    vector<Mat> maty;
    //trzeba posortować
    sort(output.begin(), output.end(), compareOrder);
    for (output_images out : output)
    {
        maty.push_back(out.my_part);
    }
    //napisać funckję do łączenia bloków w image.
    Mat Image2;
    hconcat(maty[0], maty[1], Image2);
    resize(Image2, Image2, Size((1034/2.1), 1024), INTER_LINEAR);
    return Image2;
}
Mat One_Thread_Benchmark(Mat Image)
{
    for (int i = 1; i < 2; i = i + 2)
    {
        blur(Image, Image, Size( i, i ), Point(-1,-1) );
    }
    resize(Image, Image, Size((1034/2.1), 1024), INTER_LINEAR);
    return Image;
}