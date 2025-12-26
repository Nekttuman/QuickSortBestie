#pragma once

#include <utility>
#include <cstddef>



#ifdef ENABLE_INSERTION_SORT
constexpr std::ptrdiff_t INSERTION_SORT_THRESHOLD = 63;
#endif

// ======================================================
// Insertion Sort
// ======================================================

template<typename T, typename Compare>
void insertion_sort(T* first, T* last, Compare comp)
{
    for (T* i = first + 1; i < last; ++i)
    {
#ifdef ENABLE_MOVE_SEMANTICS
        T key = std::move(*i);
#else
        T key = *i;
#endif
        T* j = i - 1;

        while (j >= first && comp(key, *j))
        {
#ifdef ENABLE_MOVE_SEMANTICS
            *(j + 1) = std::move(*j);
#else
            *(j + 1) = *j;
#endif
            --j;
        }

#ifdef ENABLE_MOVE_SEMANTICS
        *(j + 1) = std::move(key);
#else
        *(j + 1) = key;
#endif
    }
}

// ======================================================
// Swap
// ======================================================

template<typename T>
void swap_elements(T& a, T& b)
{
#ifdef ENABLE_MOVE_SEMANTICS
    T tmp = std::move(a);
    a = std::move(b);
    b = std::move(tmp);
#else
    T tmp = a;
    a = b;
    b = tmp;
#endif
}

// ======================================================
// Median of three
// ======================================================

template<typename T, typename Compare>
T* median_of_three(T* a, T* b, T* c, Compare comp)
{
    if (comp(*a, *b))
    {
        if (comp(*b, *c)) return b;
        return comp(*a, *c) ? c : a;
    }
    else
    {
        if (comp(*a, *c)) return a;
        return comp(*b, *c) ? c : b;
    }
}

// ======================================================
// Partition
// ======================================================

template<typename T, typename Compare>
T* partition(T* first, T* last, Compare comp)
{
#ifdef ENABLE_MEDIAN_OF_THREE
    T* mid = first + (last - first) / 2;
    T* pivot_ptr = median_of_three(first, mid, last - 1, comp);
#else
    T* pivot_ptr = last - 1;
#endif

    swap_elements(*pivot_ptr, *(last - 1));

#ifdef ENABLE_MOVE_SEMANTICS
    T pivot = std::move(*(last - 1));
#else
    T pivot = *(last - 1);
#endif

    T* i = first;

    for (T* j = first; j < last - 1; ++j)
    {
        if (comp(*j, pivot))
        {
            swap_elements(*i, *j);
            ++i;
        }
    }

#ifdef ENABLE_MOVE_SEMANTICS
    *(last - 1) = std::move(*i);
    *i = std::move(pivot);
#else
    *(last - 1) = *i;
    *i = pivot;
#endif

    return i;
}

// ======================================================
// QuickSort
// ======================================================

template<typename T, typename Compare>
void quick_sort(T* first, T* last, Compare comp)
{
    // std::cout << "quick_sort: size=" << (last-first) << "\n";
#ifdef ENABLE_TAIL_RECURSION_ELIMINATION
    while (last - first > 1)
    {
    #ifdef ENABLE_INSERTION_SORT
            if (last - first <= INSERTION_SORT_THRESHOLD)
            {
                insertion_sort(first, last, comp);
                return;
            }
    #endif

        T* pivot = partition(first, last, comp);

        if (pivot - first < last - (pivot + 1))
        {
            quick_sort(first, pivot, comp);
            first = pivot + 1;
        }
        else
        {
            quick_sort(pivot + 1, last, comp);
            last = pivot;
        }
    }
#else
    if (last - first <= 1)
        return;

    #ifdef ENABLE_INSERTION_SORT
        if (last - first <= INSERTION_SORT_THRESHOLD)
        {
            insertion_sort(first, last, comp);
            return;
        }
    #endif

    T* pivot = partition(first, last, comp);
    // std::cout << "pivot index=" << (pivot-first) << "\n";
    quick_sort(first, pivot, comp);
    quick_sort(pivot + 1, last, comp);
#endif
}

// ======================================================
// Public sort()
// ======================================================

template<typename T, typename Compare>
void sort(T* first, T* last, Compare comp)
{
    if (first && last)
        quick_sort(first, last, comp);
}
