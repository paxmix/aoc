#include "lib.hpp"
#include <chrono>
#include <iostream>

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    run(25, 1);
    auto end = std::chrono::high_resolution_clock::now();
    double elapsed = (end - start).count();
    if (elapsed < 1'000'000) {
        std::cout << "Elapsed time: " << elapsed / 1'000 << "μs\n";
    } else if (elapsed < 1'000'000'000) {
        std::cout << "Elapsed time: " << elapsed / 1'000'000. << "ms\n";
    } else {
        std::cout << "Elapsed time: " << elapsed / 1'000'000'000. << "s\n";
    }
}