#ifndef __THREADPOOL_H_
#define __THREADPOOL_H_

#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>
#include <future>
#include <functional>
#include <condition_variable>


class ThreadPool
{
public:
    ThreadPool(size_t numThreads)
    {
        for (size_t i = 0; i < numThreads; ++i)
        {
            threads.emplace_back([this](std::stop_token stoken) {
                std::thread::id this_id = std::this_thread::get_id();
                std::cout << "Thread (" << this_id << ") create." << std::endl;

                while (!stoken.stop_requested()) {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        this->condition.wait(
                            lock, [this] { return !this->tasks.empty(); });
                        if (tasks.empty()) {
                            return;
                        }
                        std::cout << "Thread (" << this_id << ") start run..." << std::endl;
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
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
            std::unique_lock<std::mutex> lock(queue_mutex);
            tasks.emplace([task]()
            { (*task)(); });
        }

        condition.notify_one();

        return res;
    }

    void stop_all_thread()
    {
        for (std::jthread &thread : threads)
        {
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
    std::queue<std::function<void()>> tasks;
    std::mutex queue_mutex;
    std::condition_variable condition;
};

#endif
