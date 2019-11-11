#include "ProcessLIB.h"

int a = rand();

float sigmoid(float x){
    return 1/(1+exp(-x));
}

float sigmoid_derivative(float x){
    return sigmoid(x)*(1-sigmoid(x));
}

int maini(){
    //Independent variables
    auto input_set = xt::xarray<int>({  {0, 1, 0},
                                        {0, 0, 1},
                                        {1, 0, 0},
                                        {1, 1, 0},
                                        {1, 1, 1},
                                        {0, 1, 1},
                                        {0, 1, 0}
                                    });
    //Depdent ones
    auto labels = xt::xarray<int>({1, 0, 0, 1, 1, 0, 1});
    labels.reshape({7, 1});//To convert labels to vector
    auto weights = xt::random::rand<double>({3, 1});
    auto bias = xt::random::randint<int>({1});
    const float eta = 0.05; //Learning rate constant
    for(int epoch  = 0;epoch<25000; epoch++){
        auto inputs = input_set;
        auto XW = xt::linalg::dot(inputs, weights) +  bias;
    }

}