#include "Movement.hpp"
#include <cmath>

Movement::Movement(float3 pos, float3 dir, float speed) {
    setPosition(pos);
    setDirection(dir);
    this->speed = speed;
}

Movement::~Movement() {
    // nothing to do here
}

void Movement::setPosition(float3 pos) {
    this->position = pos;
}

void Movement::setDirection(float3 dir) {
    //normalize direction
    float length = sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
    dir.x /= length;
    dir.y /= length;
    dir.z /= length;

    this->direction = dir;
}

void Movement::setSpeed(float speed) {
    if (speed < 0) {
        this->direction.x = -this->direction.x;
        this->direction.y = -this->direction.y;
        this->direction.z = -this->direction.z;
        speed = -speed;
    }
    this->speed = speed;
}

float3 Movement::getPosition() {
    return this->position;
}

float3 Movement::getDirection() {
    return this->direction;
}

float Movement::getSpeed() {
    return this->speed;
}

void Movement::move(float time) {
    this->position.x += this->direction.x * this->speed * time;
    this->position.y += this->direction.y * this->speed * time;
    this->position.z += this->direction.z * this->speed * time;
}
