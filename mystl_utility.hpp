#ifndef MYSTL_UTILITY
#define MYSTL_UTILITY

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
    constexpr T &&forward(typename mystl::remove_reference<T>::type &t)
    {
        return static_cast<T &&>(t);
    }

    template <typename T>
    constexpr T &&forward(typename mystl::remove_reference<T>::type &&t)
    {
        return static_cast<T &&>(t);
    }
}

#endif