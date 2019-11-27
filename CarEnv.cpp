#ifndef CAR_ENV
#define CAR_ENV
#include "Objects.cpp"
#include "ProcessLIB.h"



#define max_acc  5 // 
#define max_vel 50
#define road_width 5 // m
// A control task to learn from state data returned by the program 
// Discrete control is being used.

// State consists of (State:-)
//     1. Velocity[0, 50]  - kmph
//     2. Acceleration(?)
//     3. Position
//     4. n(cars ahead)
//     5. next node
//     6. next to next node // gives us the direction to turn in
//     7. Distance from the middle of the road
//     8. distance from the previous no
//     9. Current(Previous) node


// Reward is -0.1 every second till episode is done and +1000/N for every track tile visited where N = total no of tiles
// Game is solved when agent continuously scores more than 900


//The Action space (immutable) is :
// Actions:-
//     1. Accelerate        [0, 1]                “w”
//     2. Reverse            [0,1]    //Different as max_vel(rev) is less than acc      “s”
//     3. Turn(left, right) [-1, 1] → (+, -)                  (“a”, “d”)
//     4. Brake         [0,1]          “j”
//     5. Indicator {-1, 0, 1}           “<”
//     6. Horn		    {0,1}     “lshift ; rshift”
//     //7. Enter a vehicle 	         “f”

class CarDriving{
protected:
    unsigned int max_episode_steps; //Default value = 1000
    float wheelbase;
    topologicalMap Arena;
    //Observation Variables
    std::vector<double> state; //Actual, Present State
    std::vector<std::vector<double>> linear_spaces_state; //Actual, all possible states
    std::vector<int> space_state; //Spaced, Present state
    std::vector<std::vector<int>> PossibleStates_space; //Spaced, Present state
    //Action Variables
    std::vector<double> action; //Actual, present taken action
    std::vector<std::vector<double>> linear_spaces_actions; //Actual, all possible actions
    std::vector<int> spaced_action; //Spaced, current
    std::vector<std::vector<int>> PossibleActions_space; //Spaced, all possible
    float reward; //the reward - will be calculated as aforementioned
    float prev_reward; //Need to store this when current reward has been updated
    queue<std::pair<PVector, int>> Route; //Array of nodes to be traversed in order to reach the destination following the minimum length path
    PVector position;
    vehicle *self;
    float mass; //mass of the car  - required for force calculations
    std::vector<PVector> coordinates; // Coordinates of all the nodes
    PVector cNode; //coordinates of current node
    PVector nNode; //coordinates of next node
public:
    void setMax_episode_steps(int x){
        max_episode_steps = x;
    }
    CarDriving(int startN, int endN);//Initialise action_space and observation_space //Initialising reward variables as 0
    void destroy();
    void render();
    void getPath();//called when reset() is called or whenever we choose to take it from one point to the other. - Determines the shortest path to be taken given two points.
    void setTopMap(topologicalMap A){
        Arena = A;
    }
    void createSubPath();//Determining path from current state - to be called only when a node is encountered 
    void createRoute(int x, int y); //Might be useful - for creating checkpoints etc
    std::vector<int> reset(){
        std::vector<int> a = {0, 1, 0};
        return a;
    } //Change all states back to nascent, return nascent state.

    std::tuple <std::vector<int>, float, bool> step(std::vector<int> _action);//Obs, Rewards, Done
    std::vector<int> max_action(map<std::pair<std::vector<int>, std::vector<int>>, float> Q, std::vector<int> state); //Returning the maximum Q-Valued action for a given state
    std::vector<std::vector<int>> getPossibleActions_space(){
        return PossibleActions_space;
    }

    std::vector<std::vector<int>> getPossibleStates_space(){
        return PossibleStates_space;
    }

    int getMax_episode_steps(){
        return max_episode_steps;
    }
};


CarDriving::CarDriving(int startN, int endN){//Initialise action_space and observation_space
    //Initialising reward variables as 0
    max_episode_steps = 1000;
    //action_space = std::vector<std::vector<int>>(7); - Setting up the Action Space
    reward = 0;
    prev_reward = 0;
    
    mass  = 2500; //kg
    //Setting Up the State Space:
    std::vector<double> dist_nextnode = linDiscretise(0.0, 1.0, 100);
    std::vector<double> dist_middle = linDiscretise(0.0, 1.0, 10);
    std::vector<double> speedSpace = linDiscretise(0.0, 1.0, 50);

    linear_spaces_state.push_back(dist_nextnode);
    linear_spaces_state.push_back(dist_middle);
    linear_spaces_state.push_back(speedSpace);

        //Filling in the possible states
        std::vector<int> sizes = {100, 10, 50};
        int s = LCM(sizes);
        for(int i=0;i<s; i++){
            std::vector<int> temp;
            for(int j=0;j<linear_spaces_state.size();j++){
                temp.push_back(i%linear_spaces_state[j].size());
            }
            PossibleStates_space.push_back(temp);
        }
    
    //Action Space: 
    std::vector<double> acc = linDiscretise(-0.5, 1.0, 20);
    std::vector<double> steer = linDiscretise(-1.0 ,1.0, 20);
    std::vector<double> brake = linDiscretise(0.0, 1.0, 10);

    linear_spaces_actions.push_back(acc);
    linear_spaces_actions.push_back(steer);
    linear_spaces_actions.push_back(brake);

        //Filling in all possible actions
        std::vector<int> sizes_ = {20, 20, 10};
        int s_ = LCM(sizes_);
        for(int i=0;i<s_; i++){
            std::vector<int> temp_;
            for(int j=0;j<linear_spaces_actions.size();j++){
                temp_.push_back(i%linear_spaces_actions[j].size());
            }
            PossibleActions_space.push_back(temp_);
        }

    self = new vehicle(100, 0);
    wheelbase = 2; // 2 meters

    
    //Setting up the coordinates as per the TopMap
    std::__cxx11::string f = "TOPMAP01.csv";
    topologicalMap tempMap(f);
    Arena = tempMap;

    coordinates.push_back(PVector(10, 10));
    coordinates.push_back(PVector(30, 10));
    coordinates.push_back(PVector(50, 10));
    coordinates.push_back(PVector(10, 30));
    coordinates.push_back(PVector(30, 30));
    coordinates.push_back(PVector(50, 10));
    coordinates.push_back(PVector(10, 50));
    coordinates.push_back(PVector(30, 50));
    coordinates.push_back(PVector(50, 50));
    
    createRoute(startN, endN);
}

std::vector<int> CarDriving::max_action(map<std::pair<std::vector<int>, std::vector<int>>, float> Q, std::vector<int> state){
    std::vector<float> values;
    for(int i=0;i<Q.size();i++){
        float temp = Q[make_pair(state, PossibleActions_space[i])];
        values.push_back(temp);
    }
    // To return the action vector for which values has the maximum value
    return argmax(values, PossibleActions_space);
}

std::tuple< std::vector<int>, float, bool> CarDriving::step(std::vector<int> action){
    //Returns resultant state, reward, done

    float reward;
    std::vector<int> final_state;
    bool isDone = false;
    std::vector<double> _action;
    for(int i=0;i<action.size();i++){//Evaluating true action from the linear space
        _action.push_back(linear_spaces_actions[i][action[i]]);
    }

    if (_action.size()!=0){
        float theta = _action[0];
        PVector f_applied(sin(theta), cos(theta));
        f_applied = f_applied.cross(PVector(0, 0, 1)).into(mass*self->getvelocity().dot(self->getvelocity())/(wheelbase/sin(theta)));
        f_applied = f_applied.plus(self->getorientation().into(_action[1]*max_acc));
        self->applyForce(f_applied);
        self->update(); //to update everything

        //Calculating the distance from the centre of the road
        float x1, x2, d, D;
        D  = cNode.dist(nNode);
        x1 = self->getLocation().dist(nNode);
        x2 = self->getLocation().dist(cNode);
        d = pow((x1*x1+x2*x2-D*d)/2, 0.5);

        prev_reward  = reward;
        reward -= 0.1 + 0.5*x1 + 0.6*d; //Every time this function is called
        
        
        if(x1<1){
            cNode = nNode;
            if(Route.empty()){
                isDone = true;
            }
            nNode = Route.front().first;
            Route.pop();
        }
        
        //Determining the final state
        final_state.push_back(Digitize(x1/D, linear_spaces_state[0]));
        final_state.push_back(Digitize((2*d/road_width), linear_spaces_state[1]));
        final_state.push_back(Digitize(self->getvelocity().modulus()/max_vel, linear_spaces_state[2]));
    }


    float step_reward = reward-prev_reward;
    return make_tuple(final_state, step_reward, isDone);
}

void CarDriving::createRoute(int x, int y){
    //emptying the Queue
    queue<std::pair<PVector, int>> empty;
    swap(Route, empty);

    std::vector<int> temp;
    Dijkstra sol(Arena);
    temp = sol.dijkstra(x, y);
    std::vector<PVector> X;
    for(auto a:temp){
        X.push_back(coordinates[a]);
    }

    
    for(int i=0;i<temp.size();i++)
        Route.push(make_pair(X[i], temp[i]));
}

void CarDriving::render(){
    return ;
}


#endif