#ifndef BIRD_HPP
#define BIRD_HPP

#include <vector>

#include "utils.hpp"

class Bird {
public:
    Vector2 position;
    Vector2 velocity;

    Bird(float x, float y, float vx, float vy);

    void update(const std::vector<Bird>& flock);
};

#endif // BIRD_HPP
