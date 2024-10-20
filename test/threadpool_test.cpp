#include<iostream>
#include<chrono>
#include<thread>
#include"ThreadPool.hpp"
#include <chrono>


void task(int id) {
    // std::cout << "Task " << id << " started" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    // std::cout << "Task " << id << " finished" << std::endl;
}


void threadpool_test()
{
    ThreadPool pool(4);

    for (int i = 0; i < 8; ++i) {
        pool.putTask(task, i);
    }

    sleep(3);

    pool.stop_all_thread();
}
