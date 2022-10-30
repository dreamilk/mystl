#ifndef MYSTL_VECTOR_H
#define MYSTL_VECTOR_H

#include "mystl_alloctor.hpp"
#include "mystl_iterator.hpp"

#include <utility>

namespace mystl
{
    using uint = unsigned int;

    template <typename T, typename Alloc = alloctor<T>>
    class vector
    {
    private:
        using value_type = T;
        using pointer = T *;
        using const_pointer = const T *;
        using reference = T &;
        using const_reference = const T &;

        using iterator = T *;

        Alloc data_alloctor;
        T *_content;
        uint _size;
        uint _capacity;

        void check_and_expand();

    public:
        vector(uint s = 0);

        void push_back(const T &t);

        T pop_back();
        T &operator[](uint pos);
        void reserve(uint n, const T &t = T());

        iterator begin() const;
        iterator end() const;

        uint size() const;
        uint capacity() const;
        ~vector();

        template <class... Args>
        void emplace_back(Args &&...args);
    };
}

template <class T, class Alloc>
mystl::vector<T, Alloc>::vector(uint s)
{
    _size = s;
    _capacity = s;
    _content = data_alloctor.allocate(s);
    for (uint i = 0; i < _size; ++i)
    {
        data_alloctor.construct(&_content[i]);
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
    if (_capacity < n)
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
}

template <class T, class Alloc>
T *mystl::vector<T, Alloc>::begin() const
{
    return _content;
}

template <class T, class Alloc>
T *mystl::vector<T, Alloc>::end() const
{
    return _content + _size;
}

template <class T, class Alloc>
mystl::uint mystl::vector<T, Alloc>::size() const
{
    return _size;
}

template <class T, class Alloc>
mystl::uint mystl::vector<T, Alloc>::capacity() const
{
    return _capacity;
}

template <class T, class Alloc>
void mystl::vector<T, Alloc>::check_and_expand()
{
    if (_size == _capacity)
    {
        _capacity = _capacity == 0 ? 1 : 2 * _capacity;
        T *_new_content = data_alloctor.allocate(_capacity);
        uninitialized_copy(_content, _content + _size, _new_content);
        destory(_content, _content + _size);
        data_alloctor.deallocate(_content);
        _content = _new_content;
    }
}

template <class T, class Alloc>
void mystl::vector<T, Alloc>::push_back(const T &t)
{
    check_and_expand();
    data_alloctor.construct(&_content[_size++], t);
}

template <class T, class Alloc>
template <class... Args>
void mystl::vector<T, Alloc>::emplace_back(Args &&...args)
{
    check_and_expand();
    data_alloctor.construct(&_content[_size++], std::forward<Args>(args)...);
}

template <class T, class Alloc>
mystl::vector<T, Alloc>::~vector()
{
    for (uint i = 0; i < _size; ++i)
    {
        data_alloctor.destory(&_content[i]);
    }
    data_alloctor.deallocate(_content);
}
#endif