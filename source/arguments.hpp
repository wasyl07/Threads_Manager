#pragma once

#include <vector>
#include <thread>
#include <iostream>
#include <future>


struct arguments{
    std::vector<std::vector<double>> inputs;
    std::vector<double> output;
    double x;
};
struct semafora{
    bool compute = false;
};
