#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include "FH.h"
using namespace std;

int main(){
	int n; // Number of nodes in the map
	cin >> n;
	// std::vector<std::vector<float>> coordinates;
	// for(int i=0;i<n;i++){
	// 	float x, y;
	// 	cin >> x >> y;
	// 	std::vector<float> temp = {x, y};
	// 	coordinates.push_back(temp);
	// }

	// //Save coordinates to a csv
	// modify_csv_file("Node_Coordinates.csv", coordinates);	

	//Making the TopMap
	std::vector<std::vector<int>> TopMap;
	for(int i=0;i<n;i++){
		std::vector<int> temp_(n);
		TopMap.push_back(temp_);
	}
	int nod1, nod2, distance;
	nod1 = 0;
	while(1){
		cin>>nod1;
		if(nod1<0)
			break;
		cin >> nod2 >> distance;

		TopMap[nod1-1][ nod2-1] = distance;
		TopMap[nod2-1][nod1-1] = distance;
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(TopMap[i][j]==0)
				TopMap[i][j] = -1;
		}
	}


	//Saving the TopMap
	modify_csv_file("TOPMAP01.csv", TopMap);
	return 0;
}


