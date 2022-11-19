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
        Alloc _data_alloctor;
        T *_content;
        uint _size;
        uint _capacity;

    public:
        using value_type = T;
        using pointer = T *;
        using const_pointer = const T *;
        using reference = T &;
        using const_reference = const T &;

        using difference_type = uint;

        using size_type = unsigned int;

        using iterator = T *;
        using const_iterator = const T *;

        using allocator_type = Alloc;

    private:
        void check_and_expand()
        {
            if (_size == _capacity)
            {
                _capacity = _capacity == 0 ? 1 : 2 * _capacity;
                T *_new_content = _data_alloctor.allocate(_capacity);
                mystl::uninitialized_copy(begin(), end(), _new_content);
                mystl::destory(begin(), end());
                _data_alloctor.deallocate(_content);
                _content = _new_content;
            }
        }

    public:
        explicit vector(const allocator_type &alloc = allocator_type())
        {
            _data_alloctor = alloc;
            _size = 0;
            _capacity = 0;
            _content = nullptr;
        }

        explicit vector(size_type n)
        {
            _content = _data_alloctor.allocate(n);
            for (size_type i = 0; i < n; ++i)
            {
                mystl::construct(&_content[i]);
            }
            _size = n;
            _capacity = n;
        }

        vector(const vector &x)
        {
            _content = _data_alloctor.allocate(x.size());
            _size = x.size();
            mystl::uninitialized_copy(x.begin(), x.end(), _content);
            _capacity = x.capacity();
        }

        vector(vector &&x)
        {
            _content = x._content;
            _size = x._size;
            _capacity = x._capacity;
            x._content = nullptr;
            x._size = 0;
            x._capacity = 0;
        }

        vector(size_type n, const value_type &val, const allocator_type &alloc = allocator_type());

        ~vector()
        {
            mystl::destory(begin(), end());
            _data_alloctor.deallocate(_content);
        }

        vector &operator=(const vector &x);
        vector &operator=(vector &&x);

        void assign(size_type n, const value_type &val);

        void push_back(const value_type &val)
        {
            check_and_expand();
            mystl::construct(&_content[_size++], mystl::forward<value_type>(val));
        }

        void push_back(value_type &&val)
        {
            check_and_expand();
            mystl::construct(&_content[_size++], mystl::forward<value_type>(val));
        }

        void pop_back()
        {
            mystl::destory(&_content[--_size]);
        }

        iterator insert(const_iterator position, const value_type &val);
        iterator insert(const_iterator position, value_type &&val);
        iterator erase(const_iterator position);
        iterator erase(const_iterator first, const_iterator last);

        void swap(vector &x)
        {
            mystl::swap(_data_alloctor, x._data_alloctor);
            mystl::swap(_content, x._content);
            mystl::swap(_capacity, x._capacity);
            mystl::swap(_size, x._size);
        }

        void clear()
        {
            mystl::destory(begin(), end());
            _size = 0;
        }

        template <class... Args>
        iterator emplace(const_iterator position, Args &&...args);

        template <class... Args>
        void emplace_back(Args &&...args)
        {
            check_and_expand();
            mystl::construct(&_content[_size++], mystl::forward<Args>(args)...);
        }

        void reserve(size_type n);

        size_type size() const
        {
            return _size;
        }

        void resize(size_type n);
        void resize(size_type n, const value_type &val);

        bool empty() const
        {
            return _size == 0;
        }

        size_type capacity() const
        {
            return _capacity;
        }

        void shrink_to_fit();

        iterator begin() const
        {
            return _content;
        }

        iterator end() const
        {
            return _content + _size;
        }

        reference &operator[](size_type pos)
        {
            return _content[pos];
        }

        reference at(size_type n)
        {
            return _content[n];
        }

        const_reference at(size_type n) const;

        reference back()
        {
            return _content[_size - 1];
        }

        const_reference back() const
        {
            return _content[_size - 1];
        }
        value_type *data() noexcept;
        const value_type *data() const noexcept;
    };
}

#endif