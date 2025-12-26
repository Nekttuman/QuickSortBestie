#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include "Tests.hpp"
#include "PerformanceTest.hpp"


// #define ENABLE_MOVE_SEMANTICS ON
// #define ENABLE_MEDIAN_OF_THREE ON
// #define ENABLE_INSERTION_SORT ON
#define ENABLE_TAIL_RECURSION_ELIMINATION ON

int main()
{
#ifdef ENABLE_MOVE_SEMANTICS
std::cout<<"ENABLE_MOVE_SEMANTICS ON\n";
#else
std::cout<<"ENABLE_MOVE_SEMANTICS Off\n";
#endif
#ifdef ENABLE_MEDIAN_OF_THREE
std::cout<<"ENABLE_MEDIAN_OF_THREE ON\n";
#else
std::cout<<"ENABLE_MEDIAN_OF_THREE Off\n";
#endif
#ifdef ENABLE_INSERTION_SORT
std::cout<<"ENABLE_INSERTION_SORT ON\n";
#else
std::cout<<"ENABLE_INSERTION_SORT Off\n";
#endif
#ifdef ENABLE_TAIL_RECURSION_ELIMINATION
std::cout<<"ENABLE_TAIL_RECURSION_ELIMINATION ON\n\n";
#else
std::cout<<"ENABLE_TAIL_RECURSION_ELIMINATION Off\n\n";
#endif
    
    // runTests();
    performance_tests();
    // find_best_insertion_sort_threshold();

    return 0;
}
