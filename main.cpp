#include <iostream>
#include <cstdlib>
#include "include/Tasking.h"
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;
using namespace cv;

vector<input_images> divide_image(Mat source, int blocks);

Tasking::Task_Handler Handler1;

std::mutex output_mutex;
processed_image output;

TickMeter Threads_Execution;
TickMeter Whole_Program;
TickMeter Benchmark;

Tasking::Task::Task_State Assigment(input_images input)
{
    Mat tmp;
    for (int i = 1; i < 2; i = i + 2)
    {
        blur(input.my_part, tmp, Size( i, i ), Point(-1,-1) );
        //tmp = input.my_part;
    }
    std::lock_guard<std::mutex> guard(output_mutex);
    output_images out{tmp, input.order};
    output.push_back(out);
    //std::this_thread::sleep_for(std::chrono::seconds(milis));
    return Tasking::Task::COMPLETED;
}

int main(int, char **)
{
    //Input Image. Provide file name and number of blocks.
    Whole_Program.start();
    divided_image Image = Read_image("lenna.jpg", 2);
    //Create number of threads that equals number of blocks.
    for (int i = 0; i < 2; i++)
    {
        Tasking::Task *new_task = new Tasking::Task(&Assigment, Image[i]);
    }
    //Start Image processing.
    cout << endl
         << "*************** Starting Tasks ****************" << endl
         << endl;
    Threads_Execution.start();
    Handler1.Start_all_Tasks();
    Handler1.Show_active_tasks();
    cout << endl
         << "*************** Ending Tasks ****************" << endl
         << endl;
    Handler1.End_Tasks();
    Handler1.Show_active_tasks();
    //stop timer.
    Threads_Execution.stop();
    cout << "Total time of threads execution: " << Threads_Execution.getTimeSec() << endl;
    //show processed image.
    imshow("Display window0", Process_Image(output));
    Whole_Program.stop();
    cout << "Total time of program execution: " << Whole_Program.getTimeSec() << endl;
    cout << "Percentage of time spendt on threads execution: " << (Threads_Execution.getTimeSec()/Whole_Program.getTimeSec())*100.0 << "%" << endl;
    waitKey(0);

    string image_path = samples::findFile("/home/adam/Projects/Threads_Manager/lenna.jpg");
    Mat img = imread(image_path, IMREAD_COLOR);

    Benchmark.start();
    imshow("Display window1", One_Thread_Benchmark(img));
    Benchmark.stop();
    cout << "Total time of one thread execution: " << Benchmark.getTimeSec() << endl;
    if(Benchmark.getTimeSec() - Whole_Program.getTimeSec() > 0)
    {
        cout << "MultiThreading is faster by: " << Benchmark.getTimeSec() - Whole_Program.getTimeSec() << " seconds" 
        << "(" << ((Benchmark.getTimeSec() - Whole_Program.getTimeSec())/(Benchmark.getTimeSec()))*100.0 << "%)" << endl;
    }
    else
    {
          cout << "MultiThreading is slower by: " << abs(Benchmark.getTimeSec() - Whole_Program.getTimeSec()) << " seconds " 
          << "(" << ((abs(Benchmark.getTimeSec() - Whole_Program.getTimeSec()))/(Whole_Program.getTimeSec()))*100.0 << "%)" << endl;
    }
    waitKey(0); 
    return 0;
}
