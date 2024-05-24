#ifndef BIRD_H
#define BIRD_H

#include "Movement.hpp"
#include <iostream>

class Bird : public Movement{
    private:
        int id;
        float radius;
        float weight;

    public:
        /**
         * @brief Construct a new Bird object
         * 
         * @param id
         * @param position in 3d space
         * @param direction in 3d space
         * @param speed in m/s
         * @param radius in meters
         * @param weight in kg
         * @return Bird
        */
        Bird(int id, float3 position, float3 direction, float speed, float radius, float weight);
        ~Bird();

        int getId();
        float getSize();
        float getWeight();
};

#endif