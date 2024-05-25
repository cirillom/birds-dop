#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "utils.hpp"

template <typename T>
struct component{
    T *data;
    size_t size;
    size_t capacity;
};

struct movement_data{
    float speed;
    Vector2 direction;
};

struct position_data{
    Vector2 position;
};

extern component<movement_data> movement_components;
extern component<position_data> position_components;

void init(size_t size);

void system_flock();