#ifndef MYSTL_ALLOCTOR_H
#define MYSTL_ALLOCTOR_H

// 这是一个简单的构造器

namespace mystl
{
    template <typename T>
    class alloctor
    {
    private:
        /* data */
        using uint = unsigned int;
        using value_type = T;

    public:
        alloctor(/* args */);
        value_type *allocate(uint t);
        void deallocate(T *ptr);
        void construct(T *ptr, const T &t);
        void destory(T *ptr);
        ~alloctor();
    };
}

template <class T>
mystl::alloctor<T>::alloctor()
{
}

template <class T>
void mystl::alloctor<T>::construct(T *ptr, const T &t)
{
    new (ptr) value_type(t);
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
    operator delete(ptr);
}

template <class T>
mystl::alloctor<T>::~alloctor()
{
}

#endif