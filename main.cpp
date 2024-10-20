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

void task(std::stop_token stoken)
{
    while (!stoken.stop_requested())
    {
        cout << "thread is running ..." << endl;
        sleep(2);
    }

    cout << "thread stop now." << endl;
}

template <typename Func, typename... Args>
auto putTask(Func &&func, Args &&...args) -> std::future<typename std::result_of<Func(Args...)>::type>
{
    using return_type = typename std::result_of<Func(Args...)>::type;
    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<Func>(func), std::forward<Args>(args)...)
    );
    std::future<return_type> res = task->get_future();
    (*task)();
    return res;
}

int pow(int a)
{
    cout << "excute pow" << endl;
    return a*a;
}

int main()
{
    // moodycamel::ConcurrentQueue<int> q;
    // q.enqueue(25);

    // int item;
    // bool found = q.try_dequeue(item);
    // assert(found && item == 25);

    // std::future<int> res = putTask<int(*)(int), int>(pow, 10);
    // // res.wait();
    // cout << res.get() << endl;

    // auto timeout = std::chrono::seconds(2);

    // std::future<int> fut = std::move(std::async(pow, 5));
    // std::future<int> fut1 = std::move(std::async(pow, 3));

    // // std::cout << "waiting..\n";

    // // -1-

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

    // // // -2-
    // // fut.wait();
    // // fut1.wait();


    // int result = fut.get();
    // std::cout << "\nresult : " << result << std::endl;

    // int result1 = fut1.get();
    // std::cout << "\nresult1 : " << result1 << std::endl;

    threadpool_test();
    // cJSON_test();
    // nlohmann_json_test();

    // auto mfunc = [](int x, int y)->int {
    //     return x*y;
    // };

    // function<int(int, int)> func;
    // func = mfunc;
    // func = bind(mfunc, std::placeholders::_1, 1);

    // int res;
    // res = func(4, 8);
    // cout << res << endl;

    // std::jthread thread(task);

    // sleep(5);
    // thread.request_stop();

    return 0;
}
