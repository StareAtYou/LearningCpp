#include <iostream>
#include <fstream>
#include <functional>
#include <thread>
#include "test/test.hpp"

using namespace std;


void task(std::stop_token stoken)
{
    while (!stoken.stop_requested()) {
        cout << "thread is running ..." << endl;
        sleep(2);
    }

    cout << "thread stop now." << endl;
}


int main()
{
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
