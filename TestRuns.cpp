#include "ProcessLIB.h"
#include "Objects.cpp"

//Test for path following (Between Waypoints)
int pathfollowing(){
    // path rasta(10.0,100);
    // autonomous_vehicle a(100,rasta.yat(100));
    // PVector target(600, rasta.yat(600));
    
    autonomous_vehicle a(100, 100);
    PVector target(600, 500);
     //cout <<"Target at "<<target.getx() << " ,"<< target.gety() << endl; 
    //cout << a.display().first << endl; 
   // return 0;
    std::fstream seekerpathx;
    
    seekerpathx.open("Seekerpathx4.txt", ios::out|ios::app);
    std::fstream seekerpathy;
    seekerpathy.open("Seekerpathy4.txt", ios::out|ios::app);
    a.setVelocity(PVector(0, -50, 0));
    a.update();
    cout << a.getvelocity().gety() << endl;
    cout << a.display().first << endl;
        std::pair<float, float> coords  = make_pair(0.0f, 0.0f);
    while(a.getvelocity().mag()>=0.01){
        coords = a.display();
        //cout << coords.first <<" " << coords.second << endl;
        seekerpathx << coords.first <<", ";
        seekerpathy << coords.second << ", ";
        a.seek(target);
        a.update();
    }
    cout <<" Path sought." << endl;
    seekerpathx.close();
    seekerpathy.close();
    return 0;
}


//Test for Deciding which waypoints to take

int main(){
    topologicalMap MAP;
    MAP.readmap();
    Dijkstra algo(MAP);
    std::vector<int> v = algo.dijkstra(1, 3);
    int i=0;
    int n = v.size();
    while(i<n){
        cout << v[i++] <<endl;   
    }
    return 0;
}

int testla(){
    std::vector<int> d = {1, 2, 3, 4};
    std::vector<std::vector<int>> a = {d};
    std::vector<std::vector<int>> b = {{3, 3, 4, 5}};

    std::vector<std::vector<int>> c = matrixmult_hamadard(a, b);
    int n = c.size();
    int m = c[0].size();

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++)
            cout << c[i][j] << " ";
        cout << endl;
    }
    return 0;
}

// int testANN(){
//     int numL;
//     numL = 4;
//     std::vector<int> layersizes = {3, 40, 40, 3};
//     neural_net MyfirstBrain(numL, layersizes, "AnotherBrain", 0.08);

//     std::vector<std::vector<float>> inpset = get2dvec("inputs.csv");
//     std::vector<std::vector<float>> outset = get2dvec("outputs.csv");
//     inpset.pop_back();
//     outset.pop_back();
//     //MyfirstBrain.setLearnedWeights();

//     cout << "Init Cost = " << MyfirstBrain.getCost(inpset, outset);
//     char c = getchar();
//     MyfirstBrain.stoch_learn_from(inpset, outset);
//     cout << "Final Cost  = " << MyfirstBrain.getCost(inpset, outset);
//     cout << "\nCalculating the Output for the entered inpset - \n";
//     int ch = getchar();
  
//     std::vector<float> inp = {1, 0, 1};
//     std::vector<float> out =  MyfirstBrain.getOutput(inp);
//     for(int i=0;i<3;i++){
//         cout << out[i] << endl;
//     }
//     return 0;
// }


// // int testLearning_CarEnv(){
// //     return learn();
// // }



// int ain(){
//     cout << "This is main\n";
//     return TargetSeeking();
// }

