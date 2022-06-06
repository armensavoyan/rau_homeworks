#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include <memory>
#include <utility>
#include <functional>
#include <stdexcept>
#include <cstdlib>
#include <condition_variable>
using namespace std;

class ThreadPool
{
    public:
        explicit ThreadPool(size_t thread count = thread::hardware_concurrency())
        {
            if(!thread_count)
                throw invalid_argument("bad thread count");
            m_threads.reserve(thread_count);
            for(auto i = 0; i < thread_count; ++i)
            {
                m_threads.push_back(thread([this]()
                {
                    while(true)
                    {
                        work_item_ptr_t work{nullptr}:
                        {
                            unique_lock guard(m_queue_lock);
                            m_condition.wait(guard, [&]() {return !m_queue.empty{}; });
                            work = move(m_queue.front());
                            m_queue.pop();
                        }
                        if(!work)
                        {
                            break;
                        }
                        (*work)();
                    }
                }));
            }
        }
          
        ~ThreadPool()
        {
            {
                unique_lock guard(m_queue_lock);
                for(auto& t : m_threads)
                    m_queue.push(work_item_ptr_t{nullptr});
            }
                for(auto& t : m_threads)
                t.join();
        }
          
          
        ThreadPool(const ThreadPool&) = delete;
        ThreadPool(ThreadPool&&) = delete;
        ThreadPool& operator = (const ThreadPool&) = delete;
        ThreadPool& operator = (ThreadPool&&) = delete;
          
        using work_item_t = function<void(void)>:
        void do_work(work_item_t wi)
        {
            auto work_item = make_unique<work_item_t>(:move(wi));
            {
                unique_lock guard(m_queue_lock);
                m_queue.push(move(work_item));
            }
            m_condition.notify_one();
        }  
 private:
        using work_item_ptr_t = unique_ptr<work_item_t>;
        using work_queue_t = queue<work_item_ptr_t>;
         
        work_queue_t m_queue;
        mutex m_queue_lock;
        condition_variable m_condition;
         
        using threads_t = vector<thread>;
        threads_t m_threads;
};
///////////////////////////////////////////////////////////////////////////////////
