#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "Bird.hpp"

std::vector<Bird> flock_creator(size_t size = 10){
    std::vector<Bird> flock;
    for (size_t i = 0; i < size; i++) {
        float pos_x = 0.0f, pos_y = 0.0f, pos_z = 0.0f, dir_x = 0.0f, dir_y = 0.0f, dir_z = 0.0f, speed = 0.0f, radius = 0.0f, weight = 0.0f;

        pos_x = static_cast<float>(rand() % 50);
        pos_y = static_cast<float>(rand() % 50);
        pos_z = 0.0f;

        //direction, speed, radius and weight should not be zero
        while(dir_x == 0.0f)
            dir_x = static_cast<float>(rand() % 1000);
        while(dir_y == 0.0f)
            dir_y = static_cast<float>(rand() % 1000);

            dir_z = 0.0f;

        while(speed == 0.0f)
            speed = static_cast<float>(rand() % 10);
        while(radius == 0.0f)
            radius = static_cast<float>(rand() % 150) / 100.0f;
        while(weight == 0.0f)
            weight = static_cast<float>(rand() % 10000) / 1000.0f;

        float3 position = {pos_x, pos_y, pos_z};
        float3 direction = {dir_x, dir_y, dir_z};

        Bird bird(i, position, direction, speed, radius, weight);

        flock.push_back(bird);
    }

    return flock;
}

void flock_manager(std::vector<Bird> &flock){
    for (size_t i = 0; i < flock.size(); i++) {
        
        flock[i].move(1.0f); //move the bird (1 second)

        //check if the bird collided with another bird
        for (size_t j = 0; j < flock.size(); j++) {
            if (i != j) {
                float3 pos1 = flock[i].getPosition();
                float3 pos2 = flock[j].getPosition();
                float distance = sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2) + pow(pos1.z - pos2.z, 2));
                if (distance < flock[i].getSize() + flock[j].getSize()) {
                    std::cout << "Bird " << i << " and Bird " << j << " collided" << std::endl;
                    //birds collided, change their direction and transfer momentum

                }
            }
        }
    }
}

int main() {
    srand(time(NULL));
    //create csv file
    std::ofstream file("out/bird_flight.csv");
    file << "iteration,id,x,y,radius,dx,dy\n";

    std::vector<Bird> flock = flock_creator(20);
    //run the simulation
    for (size_t i = 0; i < 10; i++) {
        std::cout << "Iteration " << i << std::endl;
        flock_manager(flock);

        for (size_t j = 0; j < flock.size(); j++) {
            float3 pos = flock[j].getPosition();
            float3 dir = flock[j].getDirection();
            float speed = flock[j].getSpeed();
            file << i << "," << flock[j].getId() << "," << pos.x << "," << pos.y << "," << flock[j].getSize() << "," << speed*dir.x << "," << speed*dir.y << "\n";
        }

        std::cout << std::endl;
    }

    file.close();

    return 0;
}