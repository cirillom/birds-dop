#include <iostream>
#include <chrono>
#include "flock-oop.hpp"
#include "bird-dop.hpp"

int main() {
    const int flock_size = 25000;
    const int iterations = 5;

    // OOP Approach
    auto start = std::chrono::high_resolution_clock::now();
    Flock oopFlock(flock_size);
    for (int i = 0; i < iterations; ++i) {
        oopFlock.update();
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "OOP Duration: " << duration.count()/iterations << " seconds\n";

    // DOP Approach
    start = std::chrono::high_resolution_clock::now();
    init(flock_size);
    for (int i = 0; i < iterations; ++i) {
        system_flock();
    }
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "DOP Duration: " << duration.count()/iterations << " seconds\n";

    return 0;
}
