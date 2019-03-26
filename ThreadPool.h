#ifndef SERVER_SIDE_THREADPOOL_H
#define SERVER_SIDE_THREADPOOL_H

#include <functional>
#include <mutex>
#include <thread>
#include <vector>
#include <condition_variable>
#include <queue>

class ThreadPool{
public:
    using Task = std::function<void()>;

    explicit  ThreadPool(std::size_t numOfThreads){
        start(numOfThreads);
    }

    ~ThreadPool(){
        stop();
    }

    template <typename F, typename... Args>

    void taskQueue(F task, Args&&... args){
        {
            std::unique_lock<std::mutex> lock{m_eventMutex};
            m_tasks.emplace(std::bind(task, std::forward<Args>(args)...));
        }

        m_eventVar.notify_one(); //notify thread that something happened.
    }

private:
    std::vector<std::thread> m_threads; //The pool
    std::condition_variable m_eventVar;
    std::mutex m_eventMutex;
    std::queue<Task> m_tasks;
    bool m_stopper = false;

    void start(std::size_t numOfThread) {

        for(auto i = 0u; i < numOfThread; ++i) {

            m_threads.emplace_back([=]{

                while(true){

                    Task task;
                    {
                        std::unique_lock<std::mutex> lock(m_eventMutex);
                        m_eventVar.wait(lock, [=] { return m_stopper || !m_tasks.empty(); });
                        if (m_stopper && m_tasks.empty())
                            break;

                        task = std::move(m_tasks.front());
                        m_tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    void stop() noexcept{
        {
            std::unique_lock<std::mutex> lock(m_eventMutex);
            m_stopper = true;
        }

        m_eventVar.notify_all();

        for(auto& thread: m_threads)
            thread.join();
    }

};


#endif //SERVER_SIDE_THREADPOOL_H
