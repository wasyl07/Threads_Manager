#include <iostream>
#include <cstdlib>
#include "include/Tasking.h"
#include <thread>
#include <mutex>
#include <chrono>
#include <fstream>

using namespace std;
using namespace cv;

Tasking::Task_Handler Handler1;

std::mutex output_mutex;

TickMeter Threads_Execution;
TickMeter Whole_Program;
TickMeter Benchmark;

processed_image output;

int Blur_intensity = 500;
int blocks = 16;

Tasking::Task::Task_State Assigment(input_images input)
{
    Mat tmp;
    for (int i = 1; i < Blur_intensity; i = i + 2)
    {
        blur(input.my_part, tmp, Size( i, i ), Point(-1,-1) );
    }
    std::lock_guard<std::mutex> guard(output_mutex);
    output_images out{tmp, input.x, input.y};
    output[input.y][input.x] = out;
    //std::this_thread::sleep_for(std::chrono::seconds(milis));
    return Tasking::Task::COMPLETED;
}

int main(int, char **)
{
    fstream fout;
    fout.open("data.csv", ios::out | ios::app);

    displacement disp = Return_Diplacement(blocks);
    processed_image output_static ( disp.rows , vector<output_images>(disp.cols));
    output = output_static;

    for(int i = 0; i <= 0; i++)
    {
    //Input Image. Provide file name and number of blocks.
    Whole_Program.start();
    //divided_image Image = Read_image("Artemis4160x6240.jpg", blocks);
    divided_image Image = Read_image("Artemis4160x6240.jpg", blocks);
    //Create number of threads that equals number of blocks.
    for (int i = 0; i < Image.size(); i++)
    {
        for(int j=0;j<Image[i].size(); j++)
        {
            Tasking::Task *new_task = new Tasking::Task(&Assigment, Image[i][j]);
        }
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
    Process_Image(output, blocks);
    Whole_Program.stop();
    cout << "Total time of program execution: " << Whole_Program.getTimeSec() << endl;
    cout << "Percentage of time spendt on threads execution: " << (Threads_Execution.getTimeSec()/Whole_Program.getTimeSec())*100.0 << "%" << endl;

    Benchmark.start();
    One_Thread_Benchmark();
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

    Handler1.Purge();

    fout << Blur_intensity << ", " 
        << Benchmark.getTimeSec() << ", "
        << Whole_Program.getTimeSec() << ", "
        << ((Benchmark.getTimeSec() - Whole_Program.getTimeSec())/(Benchmark.getTimeSec()))*100.0  << ", "
        << (Threads_Execution.getTimeSec()/Whole_Program.getTimeSec())*100.0 
        << "\n"; 

    Blur_intensity+=10;

    Threads_Execution.reset();
    Whole_Program.reset();
    Benchmark.reset();

    }

    return 0;
}
 