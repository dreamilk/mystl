#ifndef MYSTL_THREADPOOL_HPP
#define MYSTL_THREADPOOL_HPP

//为了通用性，采用c++thread

#include <thread>
#include <functional>
#include <mutex>
#include <atomic>
#include <condition_variable>

#include "mystl_vector.hpp"

namespace mystl
{
    class threadpool
    {
        using size_type = unsigned int;

    private:
        std::mutex _mtx;
        std::condition_variable _cond;
        mystl::vector<std::function<void()>> _tasks;
        mystl::vector<std::thread *> _workers;

    public:
        threadpool(size_type n)
        {
            auto f = [&]()
            {
                while(true){
                    std::unique_lock<std::mutex> lk(this->_mtx);
                    
                } };
            for (size_type i = 0; i < n; ++i)
            {
                std::thread *td = new std::thread(f);
                _workers.push_back(td);
            }
        }

        ~threadpool()
        {
        }
    };
}

#endif