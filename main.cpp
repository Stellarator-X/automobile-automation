#include <iostream>
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <cstring>
#include <bits/stdc++.h>
#include <malloc.h>
#include <fstream>
#include <cassert>
using namespace std;

#include "Objects.cpp"
#include "perceptron2.cpp"
#include "Network_Components.cpp"

//Test for path following (Between Waypoints)
int PathFollowing(){
    path rasta(10.0,100);
    autonomous_vehicle a(100,rasta.yat(100));
    PVector target(600, rasta.yat(600));
    cout <<"Target at "<<target.getx() << " ,"<< target.gety() << endl; 
    cout << a.display().first << endl; 
   // return 0;
    fstream seekerpathx;
    
    seekerpathx.open("Seekerpathx2.txt", ios::out|ios::app);
    fstream seekerpathy;
    seekerpathy.open("Seekerpathy2.txt", ios::out|ios::app);
    a.setVelocity(PVector(10, 0, 0));
    a.update();
    cout << a.getvelocity().gety() << endl;
    cout << a.display().first << endl;
    //return 0;
    pair<float, float> coords  = make_pair(0.0f, 0.0f);
    while(a.getvelocity().mag()>=0.01){

        
        coords = a.display();
        
        cout << coords.first <<" " << coords.second << endl;
        //return 0;
        seekerpathx << coords.first <<", ";
        seekerpathy << coords.second << ", ";
        a.seek(target, rasta);
       // a.followPath(rasta);
        a.update();
    }
    cout <<" Path sought." << endl;
    seekerpathx.close();
    seekerpathy.close();
    return 0;
}


//Test for Deciding which waypoints to take

int dijkstr(){
    topologicalMap MAP;
    MAP.readmap();
    Dijkstra algo(MAP);
    vector<int> v = algo.dijkstra(4, 5);
    int i=0;
    int n = v.size();
    while(i<n){
        cout << v[i++] <<endl;
        
    }
    return 0;
}

int testla(){
    vector<int> d = {1, 2, 3, 4};
    vector<vector<int>> a = {d};
    vector<vector<int>> b = {{3, 3, 4, 5}};

    vector<vector<int>> c = matrixmult_hamadard(a, b);
    int n = c.size();
    int m = c[0].size();

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++)
            cout << c[i][j] << " ";
        cout << endl;
    }
    return 0;
}

int testANN(){
    int numL;
    numL = 4;
    vector<int> layersizes = {3, 4, 4, 3};
    neural_net MyfirstBrain(numL, layersizes, "PehlaDimag");

    vector<vector<float>> inpset = get2dvec("inputs.csv");
    vector<vector<float>> outset = get2dvec("outputs.csv");
    vector<vector<float>> inp = inpset;
    vector<vector<float>> Out = outset;
   MyfirstBrain.stoch_learn_from(inpset, outset);
//    MyfirstBrain.setLearnedWeights();

    cout << endl << "Final Cost = " << MyfirstBrain.getCost(inp, Out) << endl;
    return 0;
}

int main(){
    auto start = chrono::steady_clock::now();
     testANN();
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout << "\nNeural Network Created, \n DataSet analysed, and \n Weights Learned in " <<chrono::duration<double, milli> (diff).count() << "ms" << endl;
    return 0;
}

int mains(){

    vector<int> a = {1, 2, 3, 34, 54, 6};
    vector<vector<int>> b = convert_to_2d_col(a);
    for(int i=0;i<b.size();i++){
        for(int j=0;j<b[i].size();j++)
            cout << b[i][j] << " ";
        cout << endl;
    }
    return 0;
}