#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utility.hpp>

#include <vector>

//#define BLUR_STRENGTH 90

using namespace cv;
using namespace std;

typedef vector<vector<input_images>>  divided_image;
typedef vector<vector<output_images>> processed_image;

divided_image divide_image(Mat source, int blocks);
divided_image Read_image(string file_name, int blocks);
Mat Process_Image(processed_image output, int blocks);

extern int Blur_intensity;

struct displacement{
    int rows;
    int cols;
};

displacement Return_Diplacement(int blocks)
{
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
    displacement disp {w, k};
    return disp;
}

divided_image Read_image(string file_name, int blocks)
{
    string image_path = samples::findFile("/home/adam/Projects/Threads_Manager/" + file_name);
    Mat img = imread(image_path, IMREAD_COLOR);
    //resize(img, img, Size(2560, 1440), INTER_LINEAR);
    divided_image divided_images = divide_image(img, blocks);
    return divided_images;
}

divided_image divide_image(Mat source, int blocks)
{
    displacement disp = Return_Diplacement(blocks);

    divided_image divided_images( disp.rows , vector<input_images> (disp.cols));

    int image_rows = source.rows / disp.rows;
    int image_cols = source.cols / disp.cols;

    int order = 0;

    Point p(0, 0);

    for(int i=0;i<disp.rows;i++)
    {
        for(int j = 0;j<disp.cols;j++)
        {
            Mat tmp = Mat(source, Rect(p.x, p.y, image_cols, image_rows));
            input_images *images = new input_images();
            images->my_part = tmp;
            images->x = j;
            images->y = i;
            divided_images[i][j] = *images;
            p.x += image_cols;
            order++;
        }
        p.x = 0;
        p.y += image_rows;
    }
    return divided_images;
}
Mat Process_Image(processed_image output, int blocks)
{
    //pętla wierszami.
    for (int i = 0; i < output.size(); i++)
    {
        int j = 0;
        while(output[i].size() != 1)
        {
            hconcat(output[i][j].my_part, output[i][j+1].my_part, output[i][j].my_part);
            output[i].erase(output[i].begin() + 1);
        }
    }
    //Pętla kolumnami.
    for(int i = 0; i < output.size(); i++)
    {
        while(output.size() != 1)
        {
            vconcat(output[i][0].my_part, output[i+1][0].my_part, output[i][0].my_part);
            output.erase(output.begin() + 1);
        }
    }
    resize(output[0][0].my_part, output[0][0].my_part, Size((4160), 6240), INTER_LINEAR);
    return output[0][0].my_part;
}
Mat One_Thread_Benchmark()
{
    string image_path = samples::findFile("/home/adam/Projects/Threads_Manager/Artemis4160x6240.jpg");
    Mat img = imread(image_path, IMREAD_COLOR);
    Mat tmp;
    for (int i = 1; i < Blur_intensity; i = i + 2)
    {
        blur(img, tmp, Size( i, i ), Point(-1,-1) );
    }
    //resize(tmp, tmp, Size((4160/4.5), 6240/6), INTER_LINEAR);
    return tmp;
}