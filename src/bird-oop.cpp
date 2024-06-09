#include "bird-oop.hpp"
#include <cmath>

Bird::Bird(float x, float y, float vx, float vy) : position{x, y}, velocity{vx, vy} {}

void Bird::set_flock(std::list<Bird> *flock) {
    this->flock = flock;
}

void Bird::update() {
    Vector2 alignment = {0, 0};
    Vector2 cohesion = {0, 0};
    Vector2 separation = {0, 0};

    for(auto& other : (*flock)) {
        if(other != (*this)) {
            Bird *other = other;
            alignment.x += other->velocity.x;
            alignment.y += other->velocity.y;
            cohesion.x += other->position.x;
            cohesion.y += other->position.y;
            separation.x += position.x - other->position.x;
            separation.y += position.y - other->position.y;
        }
    }
    int flock_size = flock->size();
    alignment.x /= (flock_size - 1);
    alignment.y /= (flock_size - 1);
    cohesion.x /= (flock_size - 1);
    cohesion.y /= (flock_size - 1);
    // Update the bird's velocity and position based on the rules
    velocity.x += alignment.x + cohesion.x - separation.x;
    velocity.y += alignment.y + cohesion.y - separation.y;
    position.x += velocity.x;
    position.y += velocity.y;
}
