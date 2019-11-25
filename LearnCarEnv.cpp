#include "CarEnv.cpp"
#include "ProcessLIB.h"


// *** Need to linSpace Actions
// *** Call obs/action with discretised vectors in environment class
// Plan for curriculum learning - will slowly tweak rewards to entail more stuff

CarDriving ENV;

int learn(){
    
    //Have already defined max_action
   

    ENV.setMax_episode_steps(5000);

    int n_games = 1000;

    float alpha = 0.1;
    float gamma = 0.99;
    float eps = 1.0f;

    vector<vector<int>> possibleActions = ENV.getPossibleActions_space();
    vector<vector<int>> possibleStates = ENV.getPossibleStates_space();

    map<pair<vector<int>, vector<int>>, float> Q;
    //Initialising all Q Values as 0
    for(auto action: possibleActions){
        for(auto state : possibleStates){
            Q.insert(pair<pair<vector<int>, vector<int>>, float>(make_pair(state, action), 0));
        }
    }

    float reward;
    float score;
    //Running through the episodes.
    while(n_games--){
        bool done = false;
        auto obs = ENV.reset();
        for(int i=0;i<ENV.getMax_episode_steps(); i++){
            score = 0;
            done = false;
            while(!done){
                auto state = obs;
                vector<int> act;
                if(random_random(5)<eps){
                    int acti  = random()%(possibleActions.size());
                    act = possibleActions[acti];
                }
                else{
                    act = ENV.max_action(Q, state);
                }
                std::tie(obs, reward, done) = ENV.step(act);
                auto state_ = obs;
                score+=reward;
                auto action_ = ENV.max_action(Q, state);
                Q[make_pair(state, act)] = Q[make_pair(state, act)] + alpha*(reward + gamma*Q[make_pair(state_, action_)] - Q[make_pair(state, act)] );
                state = state_;
            }
            if(eps>0.01)
            eps = eps - 2/n_games;
        }
    }

    //Storing the Q values in file.


    //Playing the game
    auto ob = ENV.reset();
    float gameScore = 0;
    auto finished = false;
    float r;
    while (!finished){
        auto currState  = ob;
        auto act1  = ENV.max_action(Q, currState);
        std::tie(ob, r, finished) = ENV.step(act1);
        ENV.render();
        gameScore+= reward;
    }
    cout << "Game finished with score  = " << gameScore << endl;

    return 0;
}