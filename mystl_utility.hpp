#ifndef MYSTL_UTILITY_HPP
#define MYSTL_UTILITY_HPP

// #include <bits/stdc++.h>

namespace mystl
{
    /// remove_reference
    template <typename T>
    struct remove_reference
    {
        using type = T;
    };

    template <typename T>
    struct remove_reference<T &>
    {
        using type = T;
    };

    template <typename T>
    struct remove_reference<T &&>
    {
        using type = T;
    };

    template <typename T>
    constexpr typename mystl::remove_reference<T>::type &&move(T &&t) noexcept
    {
        return static_cast<typename mystl::remove_reference<T>::type &&>(t);
    }

    template <typename T>
    constexpr T &&forward(typename mystl::remove_reference<T>::type &t)
    {
        return static_cast<T &&>(t);
    }

    template <typename T>
    constexpr T &&forward(typename mystl::remove_reference<T>::type &&t)
    {
        return static_cast<T &&>(t);
    }

    template <typename T>
    void swap(T &a, T &b)
    {
        auto t = mystl::move(b);
        b = mystl::move(a);
        a = mystl::move(t);
    }
}

#endif