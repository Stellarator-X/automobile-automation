#include "ProcessLIB.h"

class path{
    float yofx;
    float radius;
public :
    path(float rad, float src){
        radius  = rad;
        yofx = 50 + 20*sin(src/100);
    }
    void update(float x){
        yofx = 50 + 20*sin(x/100);
    }
    float gety(){
        return yofx;
    }
    float yat(float x){
        return 50 + 20*sin(x/100);
    }
    float getradius(){
        return radius;
    }
    
};


class RigidBody{
protected:
    float mass, momentofInertia;

    PVector position;
};
//Class Vehicle

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

pair<float, float> vehicle::display(){
    return make_pair(position.getx(), position.gety());    
}

//Class Autonomous Vehicle

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
    PVector followPath(path p);
    void seek(PVector target, path p);
    void arrive(PVector target);
    
    bool inProximity(PVector target){
        return (this->position.dist(target) < r);
    }

    
//    bool isInRange(obstacle obj);
};

PVector autonomous_vehicle::followPath(path p){
    //claculating displacement after 0.1 second
    PVector additionalForce = PVector(0, 0, 0);
    PVector pnext = position.plus(velocity.into(0.1));
    PVector ideal = PVector(pnext.getx(), p.yat(pnext.getx()));
    //if(pnext.dist(ideal)>=p.getradius())
    {
        PVector ideal2 = pnext.plus(ideal).upon(2);
        additionalForce.add(ideal.minus(pnext));
    }
    return additionalForce;
}

void autonomous_vehicle::seek(PVector target, path p){
    PVector vdesired = target.sub(target, position);
    PVector steering = target.sub(vdesired, velocity);
    steering.setMag(maxforce);
    applyForce(steering.plus(followPath(p)));
    if(this->inProximity(target))
        mapx(speed, maxspeed, 0, r, 0.01, this->position.dist(target));
}



void autonomous_vehicle::arrive(PVector target){
    mapx(speed, maxspeed, 0, 5, 0, position.dist(target));   
}


/*
bool autonomous_vehicle::isInRange(obstacle obj){
    PVector a;
    a = a.sub(position, obj.getPosition);
    return (a.mag()<obj.getrad());
}
*/

//</Autonomous Vehicle>


// # Ackermann Drive
class AckermanV: public autonomous_vehicle
{
	//empty so far - controls depend on how the graphics work out
};


//Setting up a Dubin's path - given the current and the next two nodes
//

path setDubinsPath(pair<float, float> c1, pair<float, float> c1, pair<float, float> c1){
	 
