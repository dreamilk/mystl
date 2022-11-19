#ifndef MYSTL_ITERATOR_HPP
#define MYSTL_ITERATOR_HPP

namespace mystl
{

    template <typename T>
    struct iterator_traits
    {
        using value_type = typename T::value_type;
        // using iterator_category = typename T::iterator_category;
        using difference_type = typename T::difference_type;
        using pointer = typename T::pointer;
        using reference = typename T::reference;
    };

}

#endif