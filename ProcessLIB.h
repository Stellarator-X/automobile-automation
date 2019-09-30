#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
#include <cmath>
#include <bits/stdc++.h>
using namespace std;

class PVector {  

    // The x component of the vector. 
    float x; 
    // The y component of the vector. */ 
    float y; 
    // The z component of the vector. */ 
    float z; 
 
protected :
    /** Array so that this can be temporarily used in an array context */ 
    vector<float> array = {x, y, z}; 

public:
    PVector() { //All coordinates set to zero
        x=y=z=0.0f;
    }
    PVector(float x_, float y_, float z_ = 0.0f) { //params x, y, z, initialised, z=0 by default for 2D
        x = x_; 
        y = y_; 
        z = z_; 
    }
 
    void set(float x_, float y_, float z_ = 0.0f) { // setting values, z default for 2D
        this->x = x_; 
        this->y = y_; 
        this->z = z_; 
    }
    void set(PVector v) { //Copy Constructor
        x = v.x; 
        y = v.y; 
        z = v.z; 
    } 
    void set(vector<float> source) { //Copying from an array
        if (source.size()>= 2) { 
            x = source[0]; 
            y = source[1]; 
        } 
        if (source.size()>= 3) { 
            z = source[2]; 
        } 
    } 
  
    PVector* get() {//returns a copy of the vector 
        return new PVector(x, y, z); 
    } 
 
 
    vector<float>* get(vector<float> &target) { //Returning an array form of the vector
        if (&target == NULL) { 
            return new vector<float> { x, y, z }; 
        } 
        if (target.size() >= 2) { 
            target[0] = x; 
            target[1] = y; 
        } 
        if (target.size() >= 3) { 
            target[2] = z; 
        } 
        return &target; 
    } 

    float mag() { //returns the magnitude of the vector
        return (float) sqrt(x*x + y*y + z*z); 
    } 
 
    void setMag(float m){
        float cmag = this->mag();
        x*= m/cmag;
        y*= m/cmag;
        z*= m/cmag;
    }

    void add(PVector v) { 
        x += v.getx(); 
        y += v.gety(); 
        z += v.getz(); 
    } 

    float getx(){
        return x;
    }
    float gety(){
        return y;
    }
    float getz(){
        return z;
    }
 
 
    void add(float x_, float y_, float z_) { 
        x += x_; 
        y += y_; 
        z += z_; 
    } 
 
 
  /**
   * Add two vectors 
   * @param v1 a vector 
   * @param v2 another vector 
   * @return a new vector that is the sum of v1 and v2 
   */ 
    static PVector add(PVector v1, PVector v2, PVector target = PVector(0, 0)) { 
        target.set(v1.getx() + v2.getx(), v1.gety()+v2.gety(), v1.getz()+v2.getz());
        return target;
    } 
    //Subtracting another vector from this vector
    void sub(PVector v) { 
        x -= v.getx(); 
        y -= v.gety(); 
        z -= v.getz(); 
    }
    void sub(float x_, float y_, float z_) { 
        x -= x_; 
        y -= y_; 
        z -= z_; 
    } 
    //Return the difference of two vectors
    PVector sub(PVector v1, PVector v2){ 
         PVector target;
         target.set(v1.getx()-v2.getx(), v1.gety()-v2.gety(), v1.getz()-v2.getz());
         return target;
    } 
     
    void mult(float n) { //Multiplication by a scalar
        x *= n; 
        y *= n; 
        z *= n; 
    } 

   //return the product with a scalar
    static PVector mult(PVector v, float n, PVector target = PVector(0, 0)){
        target.set(n*v.getx(), n*v.gety(), n*v.getz());
        return target;
    } 
 
 
  /**
   * Multiply each element of one vector by the elements of another vector. 
   * @param v the vector to multiply by 
   */ 
    void mult(PVector v) { 
    x *= v.getx(); 
    y *= v.gety(); 
    z *= v.getz(); 
  } 
 
 
  //Return vector with components the products of this vector and another
    static PVector mult(PVector v1, PVector v2, PVector target = PVector(0, 0)) { 
        target.set(v1.getx()*v2.getx(), v1.gety()*v2.gety(), v1.getz()*v2.getz()); 
        return target; 
    } 
 
    void div(float n) { 
       x /= n; 
       y /= n; 
       z /= n; 
    } 
  
    //Divide a vector by a scalar and return the result in a new vector. 
    static PVector div(PVector v, float n, PVector target = PVector(0,0)) { 
        target.set(v.getx()/n, v.gety()/n, v.getz()/n); 
        return target; 
    } 
 
    //Divide each element of one vector by the elements of another vector. 
    void div(PVector v) { 
        x /= v.getx(); 
        y /= v.gety(); 
        z /= v.getz(); 
  } 

   // Divide each element of one vector by the individual elements of another 
    
    static PVector div(PVector v1, PVector v2, PVector target = PVector(0,0)) {
        target.set(v1.getx()/v2.getx(), v1.gety()/v2.gety(), v1.getz()/v2.getz()); 
        return target; 
    } 
 
 

   // Calculate the Euclidean distance between two points (considering a point as a vector object) 
 
    float dist(PVector v) { 
        float dx = x - v.getx(); 
        float dy = y - v.gety(); 
        float dz = z - v.getz(); 
        return (float) sqrt(dx*dx + dy*dy + dz*dz); 
    } 
 
 
  //Calculate the Euclidean distance between two points (considering a point as a vector object) 
    static float dist(PVector v1, PVector v2) { 
        float dx = v1.getx() - v2.getx(); 
        float dy = v1.gety() - v2.gety(); 
        float dz = v1.getz() - v2.getz(); 
        return (float) sqrt(dx*dx + dy*dy + dz*dz); 
    } 
    //Dot Product
    float dot(PVector v) { 
        return x*v.getx() + y*v.gety() + z*v.getz(); 
    } 
    
    float dot(float x_, float y_, float z_) { 
        return x*x_ + y*y_ + z*z_; 
    } 
    static float dot(PVector v1, PVector v2) { 
        return v1.getx()*v2.getx() + v1.gety()*v2.gety() + v1.getz()*v2.getz(); 
    } 
 
    //Cross Product
    PVector cross(PVector v, PVector target = PVector(0,0)) { 
        float crossX = y * v.getz() - v.gety() * z; 
        float crossY = z * v.getx() - v.getz() * x; 
        float crossZ = x * v.gety() - v.getx() * y; 
        target.set(crossX, crossY, crossZ); 
        return target; 
    } 
 
 
    static PVector cross(PVector v1, PVector v2, PVector target = PVector(0,0)) { 
        float crossX = v1.y * v2.z - v2.y * v1.z; 
        float crossY = v1.z * v2.x - v2.z * v1.x; 
        float crossZ = v1.x * v2.y - v2.x * v1.y; 
        target.set(crossX, crossY, crossZ); 
        return target; 
    } 
 
 
    //Normalising the vector
    void normalize() { 
        float m = this->mag(); 
        if (m != 0 && m != 1) { 
            this->div(m); 
        } 
    } 

    PVector normalize(PVector target) { 
        float m = this->mag(); 
        if (m > 0) { 
            target.set(x/m, y/m, z/m); 
        } 
        else { 
        target.set(x, y, z); 
        } 
        return target; 
    } 


    //Limiting the magnitude of the vector
    void limit(float max) { 
        if (this->mag() > max) { 
            this->normalize(); 
        this->mult(max); 
        } 
    } 
 
 
  /**
   * Calculate the angle of rotation for this vector (only 2D vectors) 
   * @return the angle of rotation 
   */ 
    float heading2D() { 
        float angle = (float) atan(-y/x); 
        return -1*angle; 
    } 
 
 
  /**
   * Calculate the angle between two vectors, using the dot product 
   * @param v1 a vector 
   * @param v2 another vector 
   * @return the angle between the vectors 
   */ 
    static float angleBetween(PVector v1, PVector v2) { 
        double dot = v1.getx() * v2.getx() + v1.gety() * v2.gety() + v1.getz() * v2.getz(); 
        double v1mag = sqrt(v1.getx() * v1.getx() + v1.gety() * v1.gety() + v1.getz() * v1.getz()); 
        double v2mag = sqrt(v2.getx() * v2.getx() + v2.gety() * v2.gety() + v2.getz() * v2.getz()); 
        return (float) acos(dot / (v1mag * v2mag)); 
    } 
 
 /*
    string toString() { 
    return "[ " + itoa(x) + ", " + y + ", " + z + " ]"; 
  } 
 */
 
  /**
   * Return a representation of this vector as a float array. This is only for 
   * temporary use. If used in any other fashion, the contents should be copied 
   * by using the get() command to copy into your own array. 
    
    float[] array() { 
    if (array == null) { 
      array = new float[3]; 
    } 
    array[0] = x;  
    array[2] = z; 
    return array; 
  } 
}
*/
};

class BasisVector:public PVector{
protected:  
    PVector up, forward, side;//such that side = fwdXUp
public :
    BasisVector(){}
    BasisVector(PVector fwd, PVector Up);
     void update(PVector fwd);
};

BasisVector::BasisVector(PVector fwd, PVector Up){
    forward = fwd;
    up = Up; 
    side = forward.cross(up);
}

void BasisVector::update(PVector fwd){
    PVector f = fwd;
    f.normalize();
    PVector upapprox = up;
    forward = f;
    side = f.cross(upapprox);
    up  = side.cross(forward);

}

void mapx(float &y, float ymax, float ymin, float xatymax, float xatymin, float xcurr){
    y = ymax + (xcurr - xatymax)*(ymax-ymin)/(xatymax-xatymin);
}
