#include "Base.hpp"
#include <iostream>
#include <chrono>


static std::chrono::_V2::steady_clock::time_point start;

void clock_start()
{
    start = std::chrono::steady_clock::now();
}

void clock_end()
{
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Cost time: " << elapsed_seconds.count() << "s\n";
}
