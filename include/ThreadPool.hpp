#ifndef __THREADPOOL_H_
#define __THREADPOOL_H_

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <future>
#include <functional>
#include <atomic>
#include <condition_variable>
#include "concurrentqueue/concurrentqueue.h"


class ThreadPool
{
public:
    ThreadPool(size_t numThreads)
    {
        isFinish.store(true);

        for (size_t i = 0; i < numThreads; ++i)
        {
            threads.emplace_back([this](std::stop_token stoken) {
                std::thread::id this_id = std::this_thread::get_id();
                std::cout << "Thread (" << this_id << ") create." << std::endl;

                while (!stoken.stop_requested()) {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> mlock(thread_mutex);
                        condition.wait(mlock, [this](){
                            return tasks.size_approx() || !isFinish.load();
                        });

                        bool status = this->tasks.try_dequeue(task);
                        if (!status) {
                            // std::cout << "Queue pop failed." << std::endl;
                            continue;
                        }
                    }

                    task();
                }

                std::cout << "Thread (" << this_id << ") finish." << std::endl;
            });
        }
    }

    template <typename Func, typename... Args>
    auto putTask(Func &&func, Args &&...args) -> std::future<typename std::result_of<Func(Args...)>::type>
    {
        using return_type = typename std::result_of<Func(Args...)>::type;
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<Func>(func), std::forward<Args>(args)...));
        std::future<return_type> res = task->get_future();
        {
            tasks.try_enqueue([task]()
            { (*task)(); });
        }

        condition.notify_one();
        return res;
    }

    void stop_all_thread()
    {
        isFinish.store(false);

        for (std::jthread &thread : threads) {
            thread.request_stop();
        }

        condition.notify_all();
    }

    ~ThreadPool()
    {
        stop_all_thread();
    }


private:
    std::vector<std::jthread> threads;
    moodycamel::ConcurrentQueue<std::function<void()>> tasks;
    std::condition_variable condition;
    std::mutex thread_mutex;
    std::atomic<bool> isFinish;
};

#endif
