
#pragma once

#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <iostream>
#include <algorithm>
#include "Alg.hpp"

// ======================================================
// Измерение времени
// ======================================================

template<typename Func>
long long measure_time_ms(Func f)
{
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

// ======================================================
// Генераторы данных
// ======================================================

std::vector<int> gen_ints(std::size_t n)
{
    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist(0, 1'000'000);

    std::vector<int> v(n);
    for (auto& x : v) x = dist(rng);
    return v;
}

std::vector<double> gen_doubles(std::size_t n)
{
    std::mt19937 rng(42);
    std::uniform_real_distribution<double> dist(0.0, 1'000'000.0);

    std::vector<double> v(n);
    for (auto& x : v) x = dist(rng);
    return v;
}

std::vector<std::string> gen_strings(std::size_t n)
{
    std::mt19937 rng(42);
    std::uniform_int_distribution<int> len_dist(5, 20);
    std::uniform_int_distribution<int> char_dist('a', 'z'); // int!

    std::vector<std::string> v(n);

    for (auto& s : v)
    {
        int len = len_dist(rng);
        s.reserve(len);

        for (int i = 0; i < len; ++i)
            s.push_back(static_cast<char>(char_dist(rng)));
    }

    return v;
}

struct Item
{
    int key;
    std::string payload;
};

std::vector<Item> gen_items(std::size_t n)
{
    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist(0, 1'000'000);

    std::vector<Item> v(n);
    for (auto& x : v)
    {
        x.key = dist(rng);
        x.payload = "data_" + std::to_string(x.key);
    }
    return v;
}

std::vector<int> gen_nearly_sorted(std::size_t n)
{
    std::vector<int> v(n);
    for (std::size_t i = 0; i < n; ++i)
        v[i] = static_cast<int>(i);

    if (n > 10)
    {
        std::swap(v[n / 3], v[n / 2]);
        std::swap(v[n / 4], v[n / 5]);
    }
    return v;
}

std::vector<int> gen_duplicates(std::size_t n)
{
    return std::vector<int>(n, 42);
}

// ======================================================
// Универсальный запуск теста
// ======================================================

template<typename T, typename Compare>
void run_perf_test(const std::string& name,
                   const std::vector<T>& data,
                   Compare comp,
                   int iterations = 5)
{
    // ---------- Warm-up
    {
        auto warmup = data;
        sort(warmup.data(), warmup.data() + warmup.size(), comp);
    }

    long long total_time = 0;

    for (int i = 0; i < iterations; ++i)
    {
        auto v = data;

        total_time += measure_time_ms([&]() {
            sort(v.data(), v.data() + v.size(), comp);
        });
    }

    long long avg_time = total_time / iterations;

    // Проверка корректности (после последнего прогона)
    auto check = data;
    sort(check.data(), check.data() + check.size(), comp);

    bool ok = std::is_sorted(check.begin(), check.end(),
        [&](const T& a, const T& b) { return comp(a, b); });

    std::cout << name
              << ": avg " << avg_time << " ns"
              << " (" << iterations << " runs)"
              << (ok ? "" : "  [ERROR]")
              << '\n';
}

// ======================================================
// Главная функция performance-тестов
// ======================================================

void performance_tests()
{
    constexpr std::size_t N = 10'000;

    std::cout << "\n==============================\n";
    std::cout << "PERFORMANCE TESTS\n";
    std::cout << "N = " << N << "\n";
    std::cout << "==============================\n\n";




    run_perf_test(
        "int (random)",
        gen_ints(N),
        [](int a, int b) { return a < b; }
    );

    run_perf_test(
        "double (random)",
        gen_doubles(N),
        [](double a, double b) { return a < b; }
    );

    run_perf_test(
        "string (random)",
        gen_strings(N / 5),
        [](const std::string& a, const std::string& b) { return a < b; }
    );

    run_perf_test(
        "struct (key sort)",
        gen_items(N / 5),
        [](const Item& a, const Item& b) { return a.key < b.key; }
    );

    run_perf_test(
        "int (nearly sorted)",
        gen_nearly_sorted(N),
        [](int a, int b) { return a < b; }
    );

    run_perf_test(
        "int (many duplicates)",
        gen_duplicates(N),
        [](int a, int b) { return a < b; }
    );

    std::cout << "\n";
}
#include <fstream>

void find_best_insertion_sort_threshold()
{    

    constexpr std::size_t N = 10'000;

    std::vector<double> avg_times(127, 0.0); // для порогов 2..128

    // Генераторы данных
    auto data_int = gen_ints(N);
    auto data_nearly = gen_nearly_sorted(N);
    auto data_duplicates = gen_duplicates(N);

    std::cout << "=== Finding best INSERTION_SORT_THRESHOLD ===\n";

    std::ofstream fout("thresholds.csv");
    fout << "threshold,avg_time_ns\n"; // заголовок CSV

    for (std::size_t threshold = 2; threshold <= 128; ++threshold)
    {
        long long total_time = 0;

        for (int iter = 0; iter < 10; ++iter)
        {
            auto v1 = data_int;
            total_time += measure_time_ms([&]() {
                const std::size_t INSERTION_SORT_THRESHOLD_LOCAL = threshold;
                sort(v1.data(), v1.data() + v1.size(),
                     [](int a, int b) { return a < b; });
            });

            // auto v2 = data_nearly;
            // total_time += measure_time_ms([&]() {
            //     const std::size_t INSERTION_SORT_THRESHOLD_LOCAL = threshold;
            //     sort(v2.data(), v2.data() + v2.size(),
            //          [](int a, int b) { return a < b; });
            // });

            // auto v3 = data_duplicates;
            // total_time += measure_time_ms([&]() {
            //     const std::size_t INSERTION_SORT_THRESHOLD_LOCAL = threshold;
            //     sort(v3.data(), v3.data() + v3.size(),
            //          [](int a, int b) { return a < b; });
            // });
        }

        avg_times[threshold - 2] = static_cast<double>(total_time) / (10 );

        std::cout << "Threshold = " << threshold
                  << ", avg time = " << avg_times[threshold - 2] << " ns\n";

        fout << threshold << "," << avg_times[threshold - 2] << "\n";
    }

    auto min_it = std::min_element(avg_times.begin(), avg_times.end());
    std::size_t best_threshold = std::distance(avg_times.begin(), min_it) + 2;

    std::cout << "\nBest INSERTION_SORT_THRESHOLD = "
              << best_threshold
              << " (avg time = " << *min_it << " ns)\n";

    fout.close();
}

