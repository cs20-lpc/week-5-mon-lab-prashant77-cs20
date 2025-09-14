#ifndef UNSORTED_LIST_HPP
#define UNSORTED_LIST_HPP

#include "List.hpp"

template <typename T>
class UnsortedList : public List<T> {
    public:
        // default constructor
        UnsortedList() { }

        // destructor
        virtual ~UnsortedList() { }

        // remove the first element that contains the given value (argument)
        virtual void removeValue(const T&) = 0;

        // check if an element exists that contains the given value (argument)
        virtual bool search(const T&) const = 0;
};

#endif
