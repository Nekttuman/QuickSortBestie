#include "Tests.hpp"
#include "Alg.hpp"

#include <iostream>


void test_empty() {
    int* a = nullptr;
    sort(a, a, [](int x, int y) { return x < y; });
    std::cout << "test_empty passed\n";
}
void test_single() {
    int a[] = {42};
    sort(a, a + 1, [](int x, int y) { return x < y; });
    assert(a[0] == 42);
    std::cout << "test_single passed\n";
}
void test_sorted() {
    int a[] = {1, 2, 3, 4, 5};
    sort(a, a + 5, [](int x, int y) { return x < y; });
    assert(is_sorted(a, a + 5, [](int x, int y) { return x < y; }));
    std::cout << "test_sorted passed\n";
}
void test_reverse() {
    int a[] = {5, 4, 3, 2, 1};
    sort(a, a + 5, [](int x, int y) { return x < y; });
    assert(is_sorted(a, a + 5, [](int x, int y) { return x < y; }));
    std::cout << "test_reverse passed\n";
}
void test_duplicates() {
    int a[] = {3, 1, 2, 3, 3, 0, 1};
    sort(a, a + 7, [](int x, int y) { return x < y; });
    assert(is_sorted(a, a + 7, [](int x, int y) { return x < y; }));
    std::cout << "test_duplicates passed\n";
}
void test_descending() {
    int a[] = {1, 4, 2, 5, 3};
    sort(a, a + 5, [](int x, int y) { return x > y; });
    assert(is_sorted(a, a + 5, [](int x, int y) { return x > y; }));
    std::cout << "test_descending passed\n";
}
void test_struct() {
    Person a[] = {{"Alice", 30}, {"Bob", 25}, {"Charlie", 35}};

    sort(a, a + 3,
         [](const Person& p1, const Person& p2) { return p1.age < p2.age; });

    assert(a[0].age == 25);
    assert(a[1].age == 30);
    assert(a[2].age == 35);

    std::cout << "test_struct passed\n";
}
void runTests() {
    test_empty();
    test_single();
    test_sorted();
    test_reverse();
    test_duplicates();
    test_descending();
    test_struct();

    std::cout << "\nAll tests passed successfully!\n";
}