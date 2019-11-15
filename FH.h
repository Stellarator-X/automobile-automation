#ifndef FileH
#define FileH
#include "ProcessLIB.h"
#include <fstream>

/*Actions we Need to perform
    * Creating the file per layer, initilising with the random weights and bias
*/

template<class T>
void addtoCSVfile(vector<T> data,string filename){
    fstream filevar;
    filevar.open(filename, ios::app);
    size_t n = data.size();
    for(int i=0;i<n;i++){
        filevar<<data[i];
        if(i!=n-1)
            filevar<<",";        
    }
    filevar<<endl;
    filevar.close();
}

pair<vector<float>, std::streampos> getfloatvector(string filename, int getp){
    fstream filevar;
    filevar.open(filename, ios::in);
    filevar.seekg(getp, ios::beg);
    string line;
    getline(filevar, line);
    stringstream stream(line);//Used for RegEx - breaking words
    string num;
    vector<float> data;
    while(getline(stream,num, ',' )){   
        data.push_back((float)stof(num));
        //cout << num << endl;
    }
    std::streampos gtp = filevar.tellg();
    filevar.close();
    return make_pair(data, gtp);
}

vector<vector<float>> get2dvec(string filename){
    fstream file;
    vector<vector<float>> result;
    file.open(filename, ios::in);
    while(!file.eof()){
        string line;
        getline(file, line);
        stringstream stream(line);//Used for RegEx - breaking words
        string num;
        vector<float> data;
        while(getline(stream,num, ',' )){   
            data.push_back((float)stof(num));
            //cout << num << endl;
        }
        result.push_back(data);
    }
    return result;
}

template<class T>
void modify_csv_file(string filename, vector<vector<T>> dataset){
    remove(filename.c_str());
    for(vector<T> v: dataset){
        addtoCSVfile(v, filename);
    }
}



#endif