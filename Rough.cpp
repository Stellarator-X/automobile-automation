#include "ProcessLIB.h"
#include "Objects.cpp"

class AckermannVehicle : public vehicle{
    float alpha, omega;
    float wheelbase;
public :
    AckermannVehicle();
    AckermannVehicle(PVector position);
    //Need to calc force from steering angle
    void seek(PVector target);





};

void AckermannVehicle::seek(PVector position){
    
}