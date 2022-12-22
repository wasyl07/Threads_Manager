#include <iostream>
#include <cstdlib>
#include "include/Tasking.h"
#include "include/arguments.hpp"
#include <thread>
#include <mutex>
#include <chrono>

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utility.hpp>

using namespace std;
using namespace cv;

vector<input_images> divide_image(Mat source, int blocks);
Stitcher::Mode mode = Stitcher::PANORAMA;

Tasking::Task_Handler Handler1;

std::mutex output_mutex;
vector<output_images> output;

Tasking::Task::Task_State Assigment(input_images input)
{
    Mat tmp;
    for ( int i = 1; i < 31; i = i + 2 )
    {
        //blur(input.my_part, tmp, Size( i, i ), Point(-1,-1) );
        tmp = input.my_part;
    }
    std::lock_guard<std::mutex> guard(output_mutex);
    output_images out {tmp};
    output.push_back(out);
    /*
    int milis = rand()%10 + 1;
    std::this_thread::sleep_for(std::chrono::seconds(milis));
    cout <<"Task done" << endl;
    */
    return Tasking::Task::COMPLETED;
}

int main(int, char**) {

    //input image.
    std::string image_path = samples::findFile("/home/adam/Projects/Threads/Threads_Manager/szmula.jpg");
    Mat img = imread(image_path, IMREAD_COLOR);
    // /resize(img, img, Size((1034/2.1), 1024), INTER_LINEAR);    

    vector<input_images> divided_images = divide_image(img, 2);

    //Start timer
    TickMeter tm;
    for(int i=0;i<2;i++)
    {
        Tasking::Task *new_task = new Tasking::Task(&Assigment, divided_images[i]);
    }
    cout<< endl << "*************** Starting Tasks ****************" << endl << endl;
    tm.start();
    Handler1.Start_all_Tasks();
    Handler1.Show_active_tasks();
    cout<< endl << "*************** Ending Tasks ****************" << endl << endl;
    Handler1.End_Tasks();
    Handler1.Show_active_tasks();

    tm.stop();
    cout << "Total time: " << tm.getTimeSec() << endl;

    //stich
    Mat Image;
    Ptr<Stitcher> stitcher = Stitcher::create(mode);
    vector<Mat> maty;

    for(output_images out : output)
    {
        maty.push_back(out.my_part);
    }
    imshow("Display window0", maty[0]);
    imshow("Display window1", maty[1]);

    waitKey(0);

    Stitcher::Status status = stitcher->stitch(maty, Image);

    if (status != Stitcher::OK)
    {
        cout << "Can't stitch images: "<<status << endl;
        return -1;
    }

    //imshow("Display window2", Image);

    waitKey(0);

    return 0; 
}

vector<input_images> divide_image(Mat source, int blocks)
{
    vector<input_images> divided_images;

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

    int image_rows = source.rows/w;
    int image_cols = source.cols/k;

    Point p(0,0);
    int i = 0;
    for (float i = (((w/2.0)*2.0)-1.0); i >= (((w/2.0)*(-2.0)+1.0)); i--)
		{
			if(i == 0)
			{
				i--;
			}
			for (int j = (((k/2)*(-2)+1)); j <= (((k/2)*2)-1); j++)
			{
				if(j == 0)
				{
					j++;
				}
                //musi się zazębiać żeby zszyć.
                Mat tmp = Mat(source, Rect(p.x, p.y, image_cols, image_rows));
                input_images* images = new input_images();
                images->my_part = tmp;
                divided_images.push_back(*images);
                p.x+=image_cols;
			}
            p.x = 0;
            p.y += image_cols;
		}
    return divided_images;
}