#ifndef MYSTL_ALGORITHM_HPP
#define MYSTL_ALGORITHM_HPP

#include "mystl_utility.hpp"
#include "mystl_iterator.hpp"

namespace mystl
{
    template <typename InputIterator, typename T>
    InputIterator find(InputIterator first, InputIterator last, const T &t)
    {
        while (first != last && *first != t)
        {
            ++first;
        }
        return first;
    }

    template <typename Iterator, typename T>
    typename mystl::iterator_traits<Iterator>::difference_type count(Iterator first, Iterator last, const T &value)
    {
        typename mystl::iterator_traits<Iterator>::difference_type n = 0;
        while (first != last)
        {
            if (*first == value)
                ++n;
            ++first;
        }
        return n;
    }

}
#endif