#include<iostream>
#include<chrono>
#include<thread>
#include"ThreadPool.hpp"
#include <chrono>


int task(int id) {
    // std::cout << "Task " << id << " started" << std::endl;
    // std::this_thread::sleep_for(std::chrono::seconds(1));
    // std::cout << "Task " << id << " finished" << std::endl;

    std::cout << "This is task: " << id << std::endl;
    sleep(3);
    return id*id;
}


void threadpool_test()
{
    ThreadPool pool(8);
    std::vector<std::future<int>> futs;

    for (int i = 0; i < 8; ++i) {
        futs.emplace_back(pool.putTask(task, i));
    }

    for (int i=0; i<futs.size(); i++) {
        futs[i].wait();
        int res = futs[i].get();
        std::cout << res << std::endl;
    }

    // pool.stop_all_thread();
    // sleep(1);
}
