#ifndef MOVEMENT_H
#define MOVEMENT_H

typedef struct{
    float x;
    float y;
    float z;
} float3;

class Movement{
    private:
        float3 position;
        float3 direction;
        float speed;


    public:
        Movement(float3 position, float3 direction, float speed);
        ~Movement();

        void setPosition(float3 position);
        void setDirection(float3 direction);
        void setSpeed(float speed);

        float3 getPosition();
        float3 getDirection();
        float getSpeed();

        void move(float time);
};

#endif