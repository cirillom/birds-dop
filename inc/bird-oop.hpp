#ifndef BIRD_HPP
#define BIRD_HPP

#include <list>

#include "utils.hpp"
#include "updatable.hpp"

class Bird : public Updatable {
public:
    Vector2 position;
    Vector2 velocity;
    std::list<Bird> *flock;

    Bird(float x, float y, float vx, float vy);

    void set_flock(std::list<Bird> *flock);

    void update();


    bool operator==(const Bird& other) const {
        return position.x == other.position.x && position.y == other.position.y &&
               velocity.x == other.velocity.x && velocity.y == other.velocity.y;
    }

    // Overload the inequality operator
    bool operator!=(const Bird& other) const {
        return !(*this == other);
    }
};

#endif // BIRD_HPP
