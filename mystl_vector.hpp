#ifndef MYSTL_VECTOR_H
#define MYSTL_VECTOR_H

#include "mystl_alloctor.hpp"
#include "mystl_iterator.hpp"
#include "mystl_utility.hpp"

// #include <utility>

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

        using size_type = unsigned int;

        using iterator = T *;
        using const_iterator = const T *;

        using allocator_type = Alloc;

        Alloc data_alloctor;
        T *_content;
        uint _size;
        uint _capacity;

        void check_and_expand();

    public:
        explicit vector(const allocator_type &alloc = allocator_type());
        explicit vector(size_type n);
        vector(const vector &x);
        vector(vector &&x);
        vector(size_type n, const value_type &val, const allocator_type &alloc = allocator_type());
        ~vector();

        vector &operator=(const vector &x);
        vector &operator=(vector &&x);

        void assign(size_type n, const value_type &val);
        void push_back(const value_type &val);
        void push_back(value_type &&val);
        void pop_back();
        iterator insert(const_iterator position, const value_type &val);
        iterator insert(const_iterator position, value_type &&val);
        iterator erase(const_iterator position);
        iterator erase(const_iterator first, const_iterator last);
        void swap(vector &x);
        void clear();

        template <class... Args>
        iterator emplace(const_iterator position, Args &&...args);

        template <class... Args>
        void emplace_back(Args &&...args);

        void reserve(size_type n);
        size_type size() const;
        void resize(size_type n);
        void resize(size_type n, const value_type &val);
        bool empty() const;
        size_type capacity() const;
        void shrink_to_fit();

        iterator begin() const;
        iterator end() const;

        value_type &operator[](size_type pos);
        reference at(size_type n);
        const_reference at(size_type n) const;
        reference back();
        const_reference back() const;
        value_type *data() noexcept;
        const value_type *data() const noexcept;
    };
}

template <class T, class Alloc>
mystl::vector<T, Alloc>::vector(const Alloc &alloc = typename mystl::vector<T, Alloc>::allocator_type()) : data_alloctor(alloc)
{
}

template <class T, class Alloc>
mystl::vector<T, Alloc>::vector(unsigned int s)
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
void mystl::vector<T, Alloc>::reserve(mystl::uint n)
{
    if (_capacity < n)
    {
        T *_new_content = data_alloctor.allocate(n);
        mystl::uninitialized_copy(_content, _size, _new_content);
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
    data_alloctor.construct(&_content[_size++], mystl::forward<Args>(args)...);
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