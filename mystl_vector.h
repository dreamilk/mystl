#ifndef MYSTL_VECTOR_H
#define MYSTL_VECTOR_H

#include "mystl_alloctor.h"

namespace mystl
{
    using uint = unsigned int;
    template <typename T, typename Alloc = alloctor<T>>
    class vector
    {
    private:
        Alloc data_alloctor;
        T *_content;
        uint _size;
        uint _capacity;

    public:
        vector(uint s = 0, const T &t = T());
        void push_back(const T &t);
        T pop_back();
        T &operator[](uint pos);
        void reserve(uint n, const T &t = T());
        uint size();
        uint capacity();
        ~vector();
    };
}

template <class T, class Alloc>
mystl::vector<T, Alloc>::vector(uint s, const T &t)
{
    _size = s;
    _capacity = s;
    _content = data_alloctor.allocate(s);
    for (uint i = 0; i < _size; ++i)
    {
        data_alloctor.construct(&_content[i], t);
    }
}

template <class T, class Alloc>
T &mystl::vector<T, Alloc>::operator[](mystl::uint pos)
{
    return (T &)_content[pos];
}

template <class T, class Alloc>
void mystl::vector<T, Alloc>::reserve(mystl::uint n, const T &t)
{
    if (_capacity == n)
    {
        return;
    }
    else if (_capacity < n)
    {
        T *_new_content = data_alloctor.allocate(n);
        for (uint i = 0; i < _size; ++i)
        {
            data_alloctor.construct(&_new_content[i], _content[i]);
            data_alloctor.destory(&_content[i]);
        }
        data_alloctor.deallocate(_content);
        _content = _new_content;
        _capacity = n;
    }
    else
    {
        _capacity = n;
        if (_size > n)
        {
            _size = n;
        }
    }
}

template <class T, class Alloc>
mystl::uint mystl::vector<T, Alloc>::size()
{
    return _size;
}

template <class T, class Alloc>
mystl::uint mystl::vector<T, Alloc>::capacity()
{
    return _capacity;
}

template <class T, class Alloc>
void mystl::vector<T, Alloc>::push_back(const T &t)
{
    if (_size == _capacity)
    {
        T *_new_content = data_alloctor.allocate(2 * _capacity);
        for (uint i = 0; i < _size; ++i)
        {
            data_alloctor.construct(&_new_content[i], _content[i]);
            data_alloctor.destory(&_content[i]);
        }
        data_alloctor.deallocate(_content);
        _content = _new_content;
        _capacity *= 2;
    }
    _content[_size++] = t;
}

template <class T, class Alloc>
mystl::vector<T, Alloc>::~vector()
{
}
#endif