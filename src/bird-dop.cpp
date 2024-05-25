#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "bird-dop.hpp"

template <typename T>
void define_component(component<T> *c, size_t capacity){
    c->capacity = capacity;
    c->size = 0;
    c->data = (T *)malloc(capacity * sizeof(T));
}

void create_flock(size_t size, component<movement_data> *movements, component<position_data> *positions){
    for(size_t i = 0; i < size; ++i){
        float pos_x = static_cast<float>(rand() % 50);
        float pos_y = static_cast<float>(rand() % 50);
        position_data pc = {{pos_x, pos_y}};
        positions->data[positions->size++] = pc;

        movement_data mc = {0.0f, {0.0f, 0.0f}};
        while(mc.direction.x == 0.0f) mc.direction.x = static_cast<float>(rand() % 1000);
        while(mc.direction.y == 0.0f) mc.direction.y = static_cast<float>(rand() % 1000);
        while(mc.speed == 0.0f) mc.speed = static_cast<float>(rand() % 10);
        movements->data[movements->size++] = mc;
    }
}

component<movement_data> movement_components;
component<position_data> position_components;
size_t flock_size;
void init(size_t size){
    flock_size = size;
    define_component(&movement_components, flock_size);
    define_component(&position_components, flock_size);

    create_flock(flock_size, &movement_components, &position_components);
}

void system_flock(){
    for(size_t i = 0; i < flock_size; ++i){
        movement_data *mc = &movement_components.data[i];
        position_data *pc = &position_components.data[i];

        Vector2 alignment = {0, 0};
        Vector2 cohesion = {0, 0};
        Vector2 separation = {0, 0};

        for(size_t j = 0; j < flock_size; ++j){
            if(j != i){
                alignment.x += movement_components.data[j].direction.x;
                alignment.y += movement_components.data[j].direction.y;
                cohesion.x += position_components.data[j].position.x;
                cohesion.y += position_components.data[j].position.y;
                separation.x += pc->position.x - position_components.data[j].position.x;
                separation.y += pc->position.y - position_components.data[j].position.y;
            }
        }

        alignment.x /= (flock_size - 1);
        alignment.y /= (flock_size - 1);
        cohesion.x /=  (flock_size - 1);
        cohesion.y /=  (flock_size - 1);

        mc->direction.x += alignment.x + cohesion.x - separation.x;
        mc->direction.y += alignment.y + cohesion.y - separation.y;

        //normalize direction
        float length = sqrt(mc->direction.x * mc->direction.x + mc->direction.y * mc->direction.y);
        mc->direction.x /= length;
        mc->direction.y /= length;

        pc->position.x += mc->direction.x * mc->speed;
        pc->position.y += mc->direction.y * mc->speed;

        //randonmize the speed a bit
        mc->speed += static_cast<float>(rand() % 10 - 5);        
    }
}