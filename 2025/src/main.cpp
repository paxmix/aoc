#include "helpers.hpp"
#include <chrono>
#include <iostream>

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    run(12, 1);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " microseconds\n";
}
