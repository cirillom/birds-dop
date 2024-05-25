#include "flock-oop.hpp"
#include <cstdlib>

Flock::Flock(int size) {
    for (int i = 0; i < size; ++i) {
        birds.emplace_back(rand() % 100, rand() % 100, rand() % 10 - 5, rand() % 10 - 5);
    }
}

void Flock::update() {
    for (auto& bird : birds) {
        bird.update(birds);
    }
}
