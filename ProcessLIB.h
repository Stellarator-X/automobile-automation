#ifndef Processes
#define Processes
//Header Files - 
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
  //  #include "FH.h"

#ifdef _MSC_VER
#include <direct.h>
#else
#include <unistd.h>
#endif

using namespace std;

class PVector {  
    //The components of the vector 
    float x, y, z;
 
protected :
    std::vector<float> array = {x, y, z}; 

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
    void set(std::vector<float> source) { //Copying from an array
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

    std::vector<float>* get(std::vector<float> &target) { //Returning an array form of the vector
        if (&target == NULL) { 
            return new std::vector<float> { x, y, z }; 
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

    static float angleBetween(PVector v1, PVector v2) { 
        double dot = v1.getx() * v2.getx() + v1.gety() * v2.gety() + v1.getz() * v2.getz(); 
        double v1mag = sqrt(v1.getx() * v1.getx() + v1.gety() * v1.gety() + v1.getz() * v1.getz()); 
        double v2mag = sqrt(v2.getx() * v2.getx() + v2.gety() * v2.gety() + v2.getz() * v2.getz()); 
        return (float) acos(dot / (v1mag * v2mag)); 
    } 
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


std::vector<std::vector<int>> get2dvec_int(std::__cxx11::string filename){
    std::fstream file;
    std::vector<std::vector<int>> result;
    file.open(filename, ios::in);
    while(!file.eof()){
        std::__cxx11::string line;
        getline(file, line);
        stringstream stream(line);//Used for RegEx - breaking words
        std::__cxx11::string num;
        std::vector<int> data;
        while(getline(stream,num, ',' )){   
            data.push_back((int)stoi(num));
            //cout << num << endl;
        }
        result.push_back(data);
    }
    file.close();
    cout << "No of nodes in the TopMap = " << result.size() << endl;
    return result;
}


// Topological Maps

class topologicalMap{
   // std::vector<std::vector<int>> map;
    int map[100][100];
    int size;
 public :
    topologicalMap(){
        return ;
    }
    //topologicalMap(std::__cxx11::string fileName);
    void readmap();
    int getsize(){
        return size;
    }
    float valat(int x, int y){
        assert(x<=size && y<=size);
        return map[x][y];
    }
};

// topologicalMap::topologicalMap(std::__cxx11::string fileName){
//     for(int i=0;i<100;i++){
//         std::vector<int> temp(100);
//         map.push_back(temp);
//     }
//     map = get2dvec_int(fileName);
//     cout << "No. of nodes in the topMap = " << map.size() << endl;
// }

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
    int minDistance(std::vector<int> dist, std::vector<bool> sptSet);
    std::vector<int> dijkstra(int src);//Returns the minimum distances for each node form the source // We already have access to the map - hence the only parameter required is the src
    std::vector<int> dijkstra(int src, int dest);//returns the series of nodes needed to be traversed to reach the distance in least(algorithmically derivable) time
    std::vector<int> getPath(int src, int dest, std::vector<int> parent);
    void printsolution();
};

int Dijkstra::minDistance(std::vector<int> dist, std::vector<bool> sptSet){
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

std::vector<int> Dijkstra::getPath(int src, int dest, std::vector<int> parent){
    int dst = dest;
    cout <<" parents - " <<endl;
    for(int i=0;i<parent.size(); i++)
        cout << i + 1 << " - " << parent[i] << endl;
    std::vector<int> pathArray;
    while(dst!=src){
       pathArray.push_back(dst);
       dst = parent[dst]; 
    }
 //   return pathArray;
    reverse(pathArray.begin(), pathArray.end());
    return pathArray;
}

std::vector<int> Dijkstra::dijkstra(int src){
    assert(src<=Map.getsize());
    std::vector<int> result(100);
    int V = Map.getsize();

    std::vector<int> dist;
    std::vector<bool> sptSet;

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

std::vector<int> Dijkstra::dijkstra(int src, int dest){
    cout << "Src = " << src << ", Map Size = " << Map.getsize() << endl ;
    assert(src<=Map.getsize());
    std::vector<int> result(100);
    int V = Map.getsize();

    std::vector<int> dist;
    std::vector<int> parent(V, -1);
    std::vector<bool> sptSet;
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
    std::vector<int> solution  = dijkstra(s);
    int g = solution.size()-1;
    int i=0;
    while((i)<g){
        cout << solution[i++]<<endl;
    }
}

// Linear Algebra

    template<class T>
    std::vector<std::vector<T>> matrixmult(std::vector<std::vector<T>> M, std::vector<std::vector<T>> N){
        std::pair<int, int> cardM = make_pair(M.size(), (M.size()>0)?(M[0].size()):0);
        std::pair<int, int> cardN = make_pair(N.size(), (N.size()>0)?N[0].size():0);
        if(N.size()==0 || M.size()==0){
            cout << "One of the two matrices is empty\n";
        }
        assert(cardM.second==cardN.first);
        std::vector<std::vector<T>> result;
        for(int x=0;x<cardM.first;x++)
            result.push_back(std::vector<T>(cardN.second));
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
    std::vector<std::vector<T>> matrixmult_hamadard(std::vector<std::vector<T>> M, std::vector<std::vector<T>> N){
        std::pair<int, int> cardM = make_pair(M.size(), M[0].size());
        std::pair<int, int> cardN = make_pair(N.size(), N[0].size());
      //  cout << cardM.first <<", " << cardM.second <<" HX " << cardN.first <<", " << cardN.second << endl;
        assert(cardM==cardN);
        std::vector<std::vector<T>> result(cardM.first);
        for(int i=0;i<cardM.first;i++){
            for(int j=0;j<cardM.second;j++)
                result[i].push_back(M[i][j]*N[i][j]);
        }
        return result;
    }

    template<class T>
    std::vector<T> vector_add(std::vector<T> A, std::vector<T> B){
        assert(A.size() == B.size());
        std::vector<T> result;
        for(auto const &i : boost::combine(A, B)){
            T a;
            T b;
            boost::tie(a, b) = i;
            result.push_back(a+b);
        }
        return result;
    }
    
    template <class T>
    std::vector<std::vector<T>> col_to_row(std::vector<std::vector<T>> vect){
        assert(vect[0].size()==1);
        std::vector<std::vector<T>> result;
        std::vector<T> row;
        for(int i=0;i<vect.size();i++){
            row.push_back(vect[i][0]);
        }
        result.push_back(row);
        return result;
    }

    template<class T>
    std::vector<std::vector<T>> matrix_add(std::vector<std::vector<T>> A, std::vector<std::vector<T>> B){
        std::vector<std::vector<T>> result;
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
    std::vector<std::vector<T>> convert_to_2d(std::vector<T> vect){
        std::vector<std::vector<T>> result;
        result.push_back(vect);
        return result;
    }

    template<class T>
    std::vector<std::vector<T>> convert_to_2d_col(std::vector<T> vect){
        std::vector<std::vector<T>> result;
        for(int i=0;i<vect.size();i++){
            std::vector<T> temp;
            temp.push_back(vect[i]);
            result.push_back(temp);
            temp.clear();
        }
        return result;
    }

    template<class T, class t>
    std::vector<T> vector_divelts(std::vector<T> A, t n){
        std::vector<T> result;
        for(T x:A){
            result.push_back(x/n);
        }
        return result;
    }

    template<class T, class t>
    std::vector<std::vector<T>> matrix_divelts(std::vector<std::vector<T>> A, t n){
        std::vector<std::vector<T>> result;
        for(std::vector<T> a: A){
            result.push_back(vector_divelts(a, n));
        }
        return result;
    }

    template<class T, class t>
    std::vector< std::vector< std::vector<T> > > TriMatrix_divelts(std::vector<std::vector<std::vector<T>>> A, t n){
        std::vector<std::vector<std::vector<T>>> result;
        for(std::vector<std::vector<T>> a: A){
            result.push_back(matrix_divelts(a, n));
        }
        return result;
    }

    template<class T>
    std::vector<std::vector<T>> Transpose(std::vector<std::vector<T>> mat){
        std::pair<int, int> cardM = make_pair(mat.size(), mat[0].size());
        std::vector<std::vector<T>> result;
        for(int i=0;i<cardM.second;i++)
            result.push_back(std::vector<T>(cardM.first));
        for(int i=0;i<cardM.second;i++){
            for(int j=0;j<cardM.first;j++)
                result[i][j] = mat[j][i];
        }
        return result;
    }

    float MSE(std::vector<float> a, std::vector<float> b)//Mean Sq Error for the two arrays
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

    std::vector<float> diff(std::vector<float> a, std::vector<float> b){
        assert(a.size()==b.size());
        int n = a.size();
        std::vector<float> result;
        for(int i=0;i<n;i++){
            result.push_back((a[i]-b[i]));
        }
        return result;
    }
    

//

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

    int LCM (std::vector<int> A){
        int lc = 1;
        for(int i : A){
            lc = lcm(lc, i);
        }
        return lc;
    }

    template<class T>
    std::vector<double> linDiscretise(T Lbound, T Ubound, int n){
        std::vector<double> result;
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
    int Digitize(T val, std::vector<double> Dvec, bool right  = false){//Assuming that discretisation is monotonic
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
    auto argmax(std::vector<T> values, std::vector<t> space){
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
    std::vector<std::vector<double>> Box(std::vector<T> minV, std::vector<T> maxV, double precision){
        //Returns the vector of all possible vectors between the two given vectors
        std::vector<std::vector<double>> result;

        assert(minV.size()==maxV.size());
        std::vector<int> sizes;
        for(int i=0;i<minV.size();i++){
            sizes.push_back(static_cast<int>((maxV[i]-minV[i])/precision));
        }

        int _size = LCM(sizes);


        for(int i=0;i<_size;i++){
            std::vector<double> temp;

            for(int j=0;j<sizes.size();j++){
                temp.push_back(minV[j]+precision*(i%sizes[j]));
            }

            result.push_back(temp);
        }
        
        return result;
    }


    float random_random(int precision){//Returns a random float in [0, 1)
    
        // @ params - precision - no of precise digits in the float returned.
        float result;
        int num = random()%(int)(pow(10, precision));
        result = static_cast<float>(num)/pow(10, precision);
        return result;
    }
#endif
