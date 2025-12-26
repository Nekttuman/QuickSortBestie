#pragma once 

#include <cassert>
#include <string>



template<typename T, typename Compare>
bool is_sorted(T* first, T* last, Compare comp)
{
    for (T* it = first + 1; it < last; ++it)
    {
        if (comp(*it, *(it - 1)))
            return false;
    }
    return true;
}

void test_empty();

void test_single();

void test_sorted();

void test_reverse();

void test_duplicates();

void test_descending();

struct Person
{
    std::string name;
    int age;
};

void test_struct();

void runTests();