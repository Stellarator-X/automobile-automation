#ifndef Processes
#define Processes

#include <iostream>
#include <cmath>
#include <vector>
//#include "xtensor"
#include <cstring>
#include <boost/range/combine.hpp>
#include <set>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>//USE - to get INT_MAX etc
#include <chrono>
#include <cstring>
#include <tuple>
#include <ctype.h>
#include <queue>
#include <cmath>
#include <bits/stdc++.h>
#include "xtensor/xarray.hpp"
#include "xtensor/xio.hpp"
#include "xtensor/xview.hpp"
#include "xtensor/xrandom.hpp"

#ifdef _MSC_VER
#include <direct.h>
#else
#include <unistd.h>
#endif
//#include "xtensor-blas/xlinalg.hpp"

using namespace std;
using namespace boost;

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
    void set(PVector &v) { //Copy Constructor
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

    PVector plus(PVector v){
        return PVector(v.getx()+x, v.gety()+y, v.getz()+z);
    }
    //Subtracting another vector from this vector
    void sub(PVector v) { 
        x -= v.getx(); 
        y -= v.gety(); 
        z -= v.getz(); 
    }

    PVector minus(PVector v){
        return PVector(x-v.getx(), y-v.gety(), z-v.getz());
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

    PVector into(float n){
        PVector a = *this;
        a.mult(n);
        return a;
    }

    float modulus(){
        return pow(x*x + y*y + z*z , 0.5);
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

    PVector upon(float n){
        return PVector(x/n, y/n, z/n);
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
   * param v1 a vector 
   * param v2 another vector 
   * return the angle between the vectors 
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
//</PVector>

//<Basis Vector>
class BasisVector:public PVector{
protected:  
    PVector up, forward, side;//such that side = fwdXUp
public :
    BasisVector(){}
    BasisVector(PVector fwd, PVector Up);
     void update(PVector fwd);
    PVector getFwd(){
        return forward;
    }
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

// </Basis Vectors> 


//Necessary function for slowing down
void mapx(float &y, float ymax, float ymin, float xatymax, float xatymin, float xcurr){
    y = ymax + (xcurr - xatymax)*(ymax-ymin)/(xatymax-xatymin);
}




// Topological Maps

class topologicalMap{
    int map[100][100];
    int size;
public :

    void readmap();
    int getsize(){
        return size;
    }
    float valat(int x, int y){
        assert(x<=size && y<=size);
        return map[x][y];
    }
};

void topologicalMap::readmap(){
        int n;
        cin >> n;
        size = n;
        assert(size<=100);
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++)
                cin >> map[i][j];

            
        }
        cout << "Read map\n";
}


//Dijkstra's Algorithm
class Dijkstra{
    topologicalMap Map;
public:
    Dijkstra(topologicalMap &T){
        Map = T;
    }
    int minDistance(vector<int> dist, vector<bool> sptSet);
    vector<int> dijkstra(int src);//Returns the minimum distances for each node form the source // We already have access to the map - hence the only parameter required is the src
    vector<int> dijkstra(int src, int dest);//returns the series of nodes needed to be traversed to reach the distance in least(algorithmically derivable) time
    vector<int> getPath(int src, int dest, vector<int> parent);
    void printsolution();
};

int Dijkstra::minDistance(vector<int> dist, vector<bool> sptSet)
{
    int V = Map.getsize();
    int min = INT_MAX, minindex;
    for(int v=0;v<V;v++){
        if((!sptSet[v])  && dist[v]<=min){
            min = dist[v];
            minindex = v;
        }
    }

    return minindex;
}

vector<int> Dijkstra::getPath(int src, int dest, vector<int> parent)
{
    int dst = dest;
    cout <<" parents - " <<endl;
    for(int i=0;i<parent.size(); i++)
        cout << i + 1 << " - " << parent[i] << endl;
    vector<int> pathArray;
    while(dst!=src){
       pathArray.push_back(dst);
       dst = parent[dst]; 
    }
 //   return pathArray;
    reverse(pathArray.begin(), pathArray.end());
    return pathArray;
}

vector<int> Dijkstra::dijkstra(int src){
    assert(src<=Map.getsize());
    vector<int> result(100);
    int V = Map.getsize();

    vector<int> dist;
    vector<bool> sptSet;

    for(int i=0;i<V;i++){
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
    dist[src]=0;

    for(int i=0;i<V-1;i++){
        int u = minDistance(dist, sptSet);

        sptSet[u] = true;

        for(int v =0;v<V;v++){
            if(!sptSet[v] && Map.valat(u, v) && dist[u] < INT_MAX  && dist[u] + Map.valat(u, v) < dist[v]){
                dist[v] = dist[u] + Map.valat(u, v);
            }
        }
        
    }

    for(int i=0;i<V;i++){
        result[i] = dist[i];
    }
    return result;
}

vector<int> Dijkstra::dijkstra(int src, int dest){
    assert(src<=Map.getsize());
    vector<int> result(100);
    int V = Map.getsize();

    vector<int> dist;
    vector<int> parent(V, -1);
    vector<bool> sptSet;
    for(int i=0;i<V;i++){
        dist.push_back(INT_MAX);
        sptSet.push_back(false);
    }
    dist[src]=0;

    for(int i=0;i<V-1;i++){
        int u = minDistance(dist, sptSet);

        sptSet[u] = true;

        for(int v =0;v<V;v++){
            if((!sptSet[v]) && (Map.valat(u, v) > 0) && (dist[u] < INT_MAX ) && (dist[u] + Map.valat(u, v) < dist[v])){
                dist[v] = dist[u] + Map.valat(u, v);
                parent[v] = u;
            }
        }
        
    }
    return getPath(src, dest, parent);
}

void Dijkstra::printsolution(){
    int s;
    cin >> s;
    vector<int> solution  = dijkstra(s);
    int g = solution.size()-1;
    int i=0;
    while((i)<g){
        cout << solution[i++]<<endl;
    }
}

// Linear Algebra

    template<class T>
    vector<vector<T>> matrixmult(vector<vector<T>> M, vector<vector<T>> N){
        pair<int, int> cardM = make_pair(M.size(), (M.size()>0)?(M[0].size()):0);
        pair<int, int> cardN = make_pair(N.size(), (N.size()>0)?N[0].size():0);
        if(N.size()==0 || M.size()==0){
            cout << "One of the two matrices is empty\n";
        }
        assert(cardM.second==cardN.first);
        vector<vector<T>> result;
        for(int x=0;x<cardM.first;x++)
            result.push_back(vector<T>(cardN.second));
        int i, j, k=0;
        for(i=0;i<cardM.first;i++){
            for(j=0;j<cardN.second;j++){
                result[i][j]=0;//redundancy
                for(int k=0;k<cardM.second;k++)
                    result[i][j] += M[i][k]*N[k][j];
            }
        }

        return result;
    }

    template<class T>
    vector<vector<T>> matrixmult_hamadard(vector<vector<T>> M, vector<vector<T>> N){
        pair<int, int> cardM = make_pair(M.size(), M[0].size());
        pair<int, int> cardN = make_pair(N.size(), N[0].size());
      //  cout << cardM.first <<", " << cardM.second <<" HX " << cardN.first <<", " << cardN.second << endl;
        assert(cardM==cardN);
        vector<vector<T>> result(cardM.first);
        for(int i=0;i<cardM.first;i++){
            for(int j=0;j<cardM.second;j++)
                result[i].push_back(M[i][j]*N[i][j]);
        }
        return result;
    }

    template<class T>
    vector<T> vector_add(vector<T> A, vector<T> B){
        assert(A.size() == B.size());
        vector<T> result;
        for(auto const &i : combine(A, B)){
            T a;
            T b;
            boost::tie(a, b) = i;
            result.push_back(a+b);
        }
        return result;
    }
    
    template <class T>
    vector<vector<T>> col_to_row(vector<vector<T>> vect){
        assert(vect[0].size()==1);
        vector<vector<T>> result;
        vector<T> row;
        for(int i=0;i<vect.size();i++){
            row.push_back(vect[i][0]);
        }
        result.push_back(row);
        return result;
    }

    template<class T>
    vector<vector<T>> matrix_add(vector<vector<T>> A, vector<vector<T>> B){
        vector<vector<T>> result;
        //cout << "Adding "<< A.size() << "X"<<A[0].size() << " with " << B.size() << "X"<<B[0].size() << endl; 
        assert(A.size()==B.size());
        size_t n = A.size();
        for(size_t i=0;i<n;i++){
            assert(A[i].size()==B[i].size());
                result.push_back(vector_add(A[i], B[i]));
        }
        return result;
    }

    template<class T>
    vector<vector<T>> convert_to_2d(vector<T> vect){
        vector<vector<T>> result;
        result.push_back(vect);
        return result;
    }

    template<class T>
    vector<vector<T>> convert_to_2d_col(vector<T> vect){
        vector<vector<T>> result;
        for(int i=0;i<vect.size();i++){
            vector<T> temp;
            temp.push_back(vect[i]);
            result.push_back(temp);
            temp.clear();
        }
        return result;
    }

    template<class T, class t>
    vector<T> vector_divelts(vector<T> A, t n){
        vector<T> result;
        for(T x:A){
            result.push_back(x/n);
        }
        return result;
    }

    template<class T, class t>
    vector<vector<T>> matrix_divelts(vector<vector<T>> A, t n){
        vector<vector<T>> result;
        for(vector<T> a: A){
            result.push_back(vector_divelts(a, n));
        }
        return result;
    }

    template<class T, class t>
    vector< vector< vector<T> > > TriMatrix_divelts(vector<vector<vector<T>>> A, t n){
        vector<vector<vector<T>>> result;
        for(vector<vector<T>> a: A){
            result.push_back(matrix_divelts(a, n));
        }
        return result;
    }

    template<class T>
    vector<vector<T>> Transpose(vector<vector<T>> mat){
        pair<int, int> cardM = make_pair(mat.size(), mat[0].size());
        vector<vector<T>> result;
        for(int i=0;i<cardM.second;i++)
            result.push_back(vector<T>(cardM.first));
        for(int i=0;i<cardM.second;i++){
            for(int j=0;j<cardM.first;j++)
                result[i][j] = mat[j][i];
        }
        return result;
    }

    float MSE(vector<float> a, vector<float> b)//Mean Sq Error for the two arrays
    {
        assert(a.size()==b.size());
        int n = a.size();
        float result=0;
        for(int i=0;i<n;i++){
            result += pow(a[i]-b[i], 2);
        }
        result/=2*n;

        return result;
    }

    vector<float> diff(vector<float> a, vector<float> b){
        assert(a.size()==b.size());
        int n = a.size();
        vector<float> result;
        for(int i=0;i<n;i++){
            result.push_back((a[i]-b[i]));
        }
        return result;
    }
    
    template<class genit>
    genit FYShuffle(genit begin, genit end){//Shuffling the entire vector
	 size_t left = std::distance(begin, end);
     size_t  num = left;
	 while(num--){
		 genit r = begin;;
		 std::advance(r,rand()%left);
		 std::swap(*begin, *r);
		 ++begin;
		 --left;
	 }
	 return begin;
    }
	
    template<class genit>
    genit FYnShuffle(genit begin, genit end, size_t num_random){//Shuffling to the first num_random numbers in the vector
	size_t left = std::distance(begin, end);
	while(num_random--){
		genit r = begin;
		std::advance(r, rand()%left);
		std::swap(*begin, *r);
		++begin;
		--left;
	}
	return begin;
    }   

    int HCF(int a, int b){
        int max = min(a, b);
        int res = 1;
        for(int i=1;i<=max; i++){
            if(!(a%i) && !(b%i))
                res=i;
        }
        return res;
    }

    int lcm(int a, int b){
        return a*b/HCF(a, b);
    }

    int LCM (vector<int> A){
        int lc = 1;
        for(int i : A){
            lc = lcm(lc, i);
        }
        return lc;
    }

    template<class T>
    vector<double> linDiscretise(T Lbound, T Ubound, int n){
        vector<double> result;
        double l = static_cast<double>(Lbound);
        double u = static_cast<double>(Ubound);

        switch(n){
            case 0:
                return result;
            case 1:
                result.push_back(l);
                return result;
            default:
                {
                    double size = (l-u)/n;
                    for(int i=0;i<n-1;i++){
                        result.push_back(l + size*i);
                    }
                    result.push_back(u);

                    return result;
                }
        }
    }

    template<class T>
    int Digitize(T val, vector<double> Dvec, bool right  = false)//Assuming that discretisation is monotonic
    {
        double v = static_cast<double>(val);
        if(val<Dvec[0])
            return 0;
        for(int i=1;i<Dvec.size()-1;i++){
            if( v>=Dvec[i]-1 && v<Dvec[i+1])
                return i;
        }
        return Dvec.size()-1;
    }

    template<class T, class t>
    auto argmax(vector<T> values, vector<t> space){
        T max = values[0];
        int pos = 0;
        for(int i=1;i<values.size();i++){
            if(max<values[i]){
                max = values[i];
                pos = i;
            }
        }
        return space[pos];
    }

    template<class T>
    vector<vector<double>> Box(vector<T> minV, vector<T> maxV, double precision){
        //Returns the vector of all possible vectors between the two given vectors
        vector<vector<double>> result;

        assert(minV.size()==maxV.size());
        vector<int> sizes;
        for(int i=0;i<minV.size();i++){
            sizes.push_back(static_cast<int>((maxV[i]-minV[i])/precision));
        }

        int _size = LCM(sizes);


        for(int i=0;i<_size;i++){
            vector<double> temp;

            for(int j=0;j<sizes.size();j++){
                temp.push_back(minV[j]+precision*(i%sizes[j]));
            }

            result.push_back(temp);
        }
        
        return result;
    }


    float random_random(int precision)//Returns a random float in [0, 1)
    {
        // @ params - precision - no of precise digits in the float returned.
        float result;
        int num = random()%(int)(pow(10, precision));
        result = static_cast<float>(num)/pow(10, precision);
        return result;
    }
#endif
