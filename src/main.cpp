#include <iostream>
#include <chrono>
#include <list>

#include "updatable.hpp"
#include "bird-dop.hpp"
#include "bird-oop.hpp"

int main() {
    const int flock_size = 25000;
    const int iterations = 5;

    // OOP Approach
    auto start = std::chrono::high_resolution_clock::now();
    std::list<Bird> flock;
    std::list<Updatable*> updatables;
    for (int i = 0; i < flock_size; ++i) {
        Bird bird(rand() % 100, rand() % 100, rand() % 10 - 5, rand() % 10 - 5);
        flock.push_back(bird);
        updatables.push_back(&flock.back());
    }
    for (auto& bird : flock) {
        bird.set_flock(&flock);
    }

    for (int i = 0; i < iterations; i++){
        for (auto& updatable : updatables) {
            updatable->update();
        }
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
