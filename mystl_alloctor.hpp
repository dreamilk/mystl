#ifndef MYSTL_ALLOCTOR_HPP
#define MYSTL_ALLOCTOR_HPP

// 这是一个简单的构造器
#include <utility>

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
        alloctor();
        value_type *allocate(uint t);
        void deallocate(T *ptr);
        void construct(T *ptr, const T &t);
        void destory(T *ptr);
        ~alloctor();

        template <class... Args>
        void construct(T *p, Args &&...args);
    };

    template <typename T1, typename T2>
    void construct(T1 *p, const T2 &t);

    template <typename T>
    void destory(T *p);

    template <typename Iterator>
    void destory(Iterator begin, Iterator end);

    //内存管理方法
    template <typename InputIterator, typename ForwardIterator>
    inline ForwardIterator uninitialized_copy(InputIterator begin, InputIterator end, ForwardIterator result);

    template <typename ForwardIterator, typename Size, typename T>
    inline ForwardIterator uninitialized_fill_n(ForwardIterator begin, Size num, const T &t);

    template <typename ForwardIterator, typename T>
    inline ForwardIterator uninitialized_fill(ForwardIterator begin, ForwardIterator end, const T &t);
}

template <class T>
mystl::alloctor<T>::alloctor()
{
}

template <class T>
void mystl::alloctor<T>::construct(T *ptr, const T &t)
{
    new (ptr) T(t);
}

template <class T>
void mystl::alloctor<T>::destory(T *ptr)
{
    ptr->~T();
}

template <class T>
T *mystl::alloctor<T>::allocate(unsigned int t)
{
    T *data = (T *)(operator new(t * sizeof(T)));
    return data;
}

template <class T>
void mystl::alloctor<T>::deallocate(T *ptr)
{
    operator delete(static_cast<void *>(ptr));
}

template <class T>
mystl::alloctor<T>::~alloctor()
{
}

template <class T>
template <class... Args>
void mystl::alloctor<T>::construct(T *p, Args &&...args)
{
    new (p) T(std::forward<Args>(args)...);
}

template <class T1, class T2>
void mystl::construct(T1 *p, const T2 &t)
{
    new (p) T2(t);
}

template <class T>
void mystl::destory(T *p)
{
    p->~T();
}

template <class Iterator>
void mystl::destory(Iterator begin, Iterator end)
{
    for (; begin != end; ++begin)
    {
        destory(&*begin);
    }
}

template <class InputIterator, class ForwardIterator>
inline ForwardIterator mystl::uninitialized_copy(InputIterator begin, InputIterator end, ForwardIterator result)
{
    for (; begin != end; ++begin, ++result)
    {
        construct(result, *begin);
    }
    return result;
}

template <class ForwardIterator, class Size, class T>
inline ForwardIterator mystl::uninitialized_fill_n(ForwardIterator begin, Size num, const T &t)
{
    for (uint i = 0; i < num; ++i)
    {
        construct(begin + i, t);
    }
    return begin + num;
}

#endif