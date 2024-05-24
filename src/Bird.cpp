#include "Bird.hpp"

Bird::Bird(int id, float3 position, float3 direction, float speed, float radius, float weight) : Movement(position, direction, speed) {
    this->id = id;
    this->radius = radius;
    this->weight = weight;
}

Bird::~Bird() {
    // nothing to do here
}

int Bird::getId() {
    return id;
}

float Bird::getSize() {
    return radius;
}

float Bird::getWeight() {
    return weight;
}