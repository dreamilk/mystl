#ifndef MYSTL_ALLOCTOR_HPP
#define MYSTL_ALLOCTOR_HPP

// 这是一个简单的构造器
#include "mystl_utility.hpp"

namespace mystl
{

    using uint = unsigned int;

    template <typename T>
    class alloctor
    {
    private:
        /* data */
        using value_type = T;

    public:
        value_type *allocate(uint size)
        {
            value_type *ptr = (value_type *)operator new(sizeof(value_type) * size);
            return ptr;
        }

        void deallocate(value_type *ptr)
        {
            operator delete(static_cast<void *>(ptr));
        }
    };

    //其他公共方法

    template <class T1, class T2>
    void construct(T1 *p, const T2 &t)
    {
        new (p) T2(t);
    }

    template <class T>
    void destory(T *p)
    {
        p->~T();
    }

    template <class Iterator>
    void destory(Iterator begin, Iterator end)
    {
        for (; begin != end; ++begin)
        {
            mystl::destory(&*begin);
        }
    }

    template <class InputIterator, class ForwardIterator>
    inline ForwardIterator uninitialized_copy(InputIterator begin, InputIterator end, ForwardIterator result)
    {
        for (; begin != end; ++begin, ++result)
        {
            mystl::construct(result, *begin);
        }
        return result;
    }

    template <class ForwardIterator, class Size, class T>
    inline ForwardIterator uninitialized_fill_n(ForwardIterator begin, Size num, const T &t)
    {
        for (uint i = 0; i < num; ++i)
        {
            mystl::construct(begin + i, t);
        }
        return begin + num;
    }
}

#endif