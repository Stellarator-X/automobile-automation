#ifndef FileH
#define FileH
#include "ProcessLIB.h"
#include <fstream>

/*Actions we Need to perform
    * Creating the file per layer, initilising with the random weights and bias
*/

template<class T>
void addtoCSVfile(std::vector<T> data,std::__cxx11::string filename){
    std::fstream filevar;
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

std::pair<std::vector<float>, std::streampos> getfloatvector(std::__cxx11::string filename, int getp){
    std::fstream filevar;
    filevar.open(filename, ios::in);
    filevar.seekg(getp, ios::beg);
    std::__cxx11::string line;
    getline(filevar, line);
    stringstream stream(line);//Used for RegEx - breaking words
    std::__cxx11::string num;
    std::vector<float> data;
    while(getline(stream,num, ',' )){   
        data.push_back((float)stof(num));
        //cout << num << endl;
    }
    std::streampos gtp = filevar.tellg();
    filevar.close();
    return make_pair(data, gtp);
}

std::vector<std::vector<float>> get2dvec(std::__cxx11::string filename){
    std::fstream file;
    std::vector<std::vector<float>> result;
    file.open(filename, ios::in);
    while(!file.eof()){
        std::__cxx11::string line;
        getline(file, line);
        stringstream stream(line);//Used for RegEx - breaking words
        std::__cxx11::string num;
        std::vector<float> data;
        while(getline(stream,num, ',' )){   
            data.push_back((float)stof(num));
            //cout << num << endl;
        }
        result.push_back(data);
    }
    return result;
}

// std::vector<std::vector<int>> get2dvec_int(std::__cxx11::string filename){
//     std::fstream file;
//     std::vector<std::vector<int>> result;
//     file.open(filename, ios::in);
//     while(!file.eof()){
//         std::__cxx11::string line;
//         getline(file, line);
//         stringstream stream(line);//Used for RegEx - breaking words
//         std::__cxx11::string num;
//         std::vector<int> data;
//         while(getline(stream,num, ',' )){   
//             data.push_back((int)stoi(num));
//             //cout << num << endl;
//         }
//         result.push_back(data);
//     }
//     return result;
// }

template<class T>
void modify_csv_file(std::__cxx11::string filename, std::vector<std::vector<T>> dataset){
    remove(filename.c_str());
    for(std::vector<T> v: dataset){
        addtoCSVfile(v, filename);
    }
}



#endif