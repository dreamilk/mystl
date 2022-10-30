#ifndef MYSTL_ITERATOR_HPP
#define MYSTL_ITERATOR_HPP

namespace mstl
{
    template <typename Category, typename T>
    class iterator
    {
    private:
    public:
        iterator();
        iterator &operator++(int);

        ~iterator();
    };
}

template <class Category, class T>
mstl::iterator<Category, T>::iterator()
{
}

template <class Category, class T>
mstl::iterator<Category, T>::~iterator()
{
}

template <class Category, class T>
mstl::iterator<Category, T> &mstl::iterator<Category, T>::operator++(int)
{
}

#endif