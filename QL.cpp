#include "ProcessLIB.h"

//Distributing all continuous distributions into a discrete linear space
auto pos_space = linDiscretise(-1.2f, 0.6f, 20);
auto vel_space = linDiscretise(-0.07, 0.07, 20);

auto get_state(vector<float> observation){
    //The observation is actually a tuple of current state values
    //Hence we need an observation cardinality
    //For cardinality 2 as in MountainCar-v0
    int pos_bin = Digitize(observation[0], pos_space);
    int vel_bin = Digitize(observation[1], vel_space);

    return make_pair(pos_bin, vel_bin);
}

auto max_action(map<pair<vector<int>, vector<int>>, float> Q, vector<int> state, vector<int> actions){
    vector<int> values;
    vector<int> actions  = 
    for(a in actions)     
}
