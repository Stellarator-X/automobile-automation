#include "ProcessLIB.h"

class RigidBody{
protected:
    float mass, momentofInertia;

    PVector position;
};

class vehicle
{
protected:
    PVector velocity, acceleration, position;
    BasisVector orientation;
    float r, speed, maxspeed, maxforce;
public:
    vehicle(){}
    vehicle(float x, float y);
    void update();
    PVector getvelocity(){
        return velocity;
    }
    void setVelocity(PVector v){
        velocity = v;
    }
    void applyForce(PVector force);
    //void seek(PVector target);
    //void arrive(PVector target, float rad);
    pair<float, float> display();
   // void display(int a);
    //bool isInRange(obstacle obj);
};

class autonomous_vehicle: public vehicle{
protected:
    float maxspeed;
public:
    autonomous_vehicle(float x, float y){
        vehicle(x, y);
        acceleration =PVector(0, 0);
        velocity = PVector(0, 0);
        position = PVector(x, y, 0);
        vehicle::maxspeed = 5;
        maxspeed = vehicle::maxspeed/1.5;
        speed = maxspeed;
        r=6;
        maxforce = 0.3;
    }
    void seek(PVector target);
    void arrive(PVector target);
//    bool isInRange(obstacle obj);
};

vehicle::vehicle(float x, float y){
    position  = PVector(x, y);
    acceleration  = PVector(0,0);
    velocity = PVector(0,0);
    orientation = BasisVector(PVector(1, 0, 0), PVector(0, 1, 0));
    r=6;
    speed = maxspeed = 5;
    maxforce = 0.3;
}

void vehicle::update(){
    velocity.add(acceleration);
    velocity.setMag(speed);
    orientation.update(velocity);
    velocity.limit(maxspeed);
    position.add(velocity);
    acceleration.mult(0);
}

void vehicle::applyForce(PVector force){
    acceleration.add(force);
}

void autonomous_vehicle::seek(PVector target){
    PVector vdesired = target.sub(target, position);

    PVector steering = target.sub(vdesired, velocity);

    steering.setMag(maxforce);
    applyForce(steering);
}

void autonomous_vehicle::arrive(PVector target){
    mapx(speed, maxspeed, 0, 5, 0, position.dist(target));   
}

pair<float, float> vehicle::display(){
    return make_pair(position.getx(), position.gety());    
}

void display(){
   // getch();
}
/*
bool autonomous_vehicle::isInRange(obstacle obj){
    PVector a;
    a = a.sub(position, obj.getPosition);
    return (a.mag()<obj.getrad());
}
*/

