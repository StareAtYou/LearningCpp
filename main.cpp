#include <iostream>
#include <fstream>
#include <functional>
#include <thread>
#include <future>
#include <chrono>
#include "Base.hpp"
#include "test/test.hpp"
#include "concurrentqueue/concurrentqueue.h"

using namespace std;

// template <typename Func, typename... Args>
// auto putTask(Func &&func, Args &&...args) -> std::future<typename std::result_of<Func(Args...)>::type>
// {
//     using return_type = typename std::result_of<Func(Args...)>::type;
//     auto task = std::make_shared<std::packaged_task<return_type()>>(
//         std::bind(std::forward<Func>(func), std::forward<Args>(args)...)
//     );
//     std::future<return_type> res = task->get_future();
//     (*task)();
//     return res;
// }

template <typename Func, typename... Args>
auto putTask(Func &&func, Args &&...args) -> std::future<typename std::result_of<Func(Args...)>::type>
{
    // using return_type = typename std::result_of<Func(Args...)>::type;
    // auto task = std::make_shared<std::packaged_task<return_type()>>(
    //     std::bind(std::forward<Func>(func), std::forward<Args>(args)...)
    // );
    // std::future<return_type> res = task->get_future();
    // (*task)();
    // return res;

    return std::move(std::async(std::forward<Func>(func), std::forward<Args>(args)...));
}

int pow(int a)
{
    sleep(1);
    cout << "excute pow" << endl;
    return a*a;
}

int multi(int a, int b, int c)
{
    sleep(2);
    return a + b + c;
}

int main()
{
    // auto timeout = std::chrono::seconds(2);
    // clock_start();
    // std::future<int> fut = std::move(std::async(pow, 5));
    // cout << "start" << endl;
    // int res = fut.get();
    // clock_end();
    // cout << res << endl;


    std::vector<std::future<int>> futs;

    clock_start();
    for (int i=0; i<3; i++) {
        futs.emplace_back(
            putTask(multi, i, i+1, i+2)
        );
    }

    for (int i=0; i<3; i++) {
        int res = futs[i].get();
        cout << res << endl;
    }
    clock_end();

    // std::future<int> fut1 = std::move(std::async(pow, 3));

    // std::future_status future_status = fut.wait_for(timeout);
    // if (future_status != std::future_status::ready)
    // {
    //     std::cout << "2 sec timeout!\n";
    //     // return -1;
    // }

    // std::future_status future1_status = fut1.wait_for(timeout);
    // if (future1_status != std::future_status::ready)
    // {
    //     std::cout << "2 sec timeout!\n";
    //     // return -1;
    // }


    // int result = fut.get();
    // std::cout << "\nresult : " << result << std::endl;

    // int result1 = fut1.get();
    // std::cout << "\nresult1 : " << result1 << std::endl;

    // threadpool_test();

    return 0;
}
