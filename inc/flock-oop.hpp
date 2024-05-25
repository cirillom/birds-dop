#ifndef FLOCK_HPP
#define FLOCK_HPP

#include "bird-oop.hpp"
#include <vector>

class Flock {
public:
    std::vector<Bird> birds;

    Flock(int size);

    void update();
};

#endif // FLOCK_HPP
