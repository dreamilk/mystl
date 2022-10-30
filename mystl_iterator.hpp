#ifndef MYSTL_ITERATOR_HPP
#define MYSTL_ITERATOR_HPP

namespace mstl
{
    template <class Category, class T, class Distance = int,
              class Pointer = T *, class Reference = T &>
    struct iterator
    {
        typedef Category iterator_category;
        typedef T value_type;
        typedef Pointer pointer;
        typedef Reference reference;
        typedef Distance difference_type;
    };

}
#endif