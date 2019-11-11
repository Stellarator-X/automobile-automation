#include "ProcessLIB.h"

float freud(float x){
    return (1+tanh(x))/2;
}

float d_freud(float x){
    return pow(1/cosh(x), 2)/2;
}

int perceptron(){
    //Independent Variables:
        int inputs[7][3] = {  {0, 0, 0},
                            {0, 0, 1},
                            {0, 1, 0},
                            {0, 1, 1},
                            {1, 0, 0},
                            {1, 1, 0},
                            {1, 1, 1}};

    //Dependent Variable - y
        float act_outputs[7] = {0, 0.1, 0.2, 0.3, 0.3, 0.5, 0.6};
    //Changeable variables:
        float bias = 0;
        float weights[3] = {1, 1, 1};
        float cost;
        float eta = 0.00001;//Learning Parameter
        

    //Learning Loop
    for(int epochs = 0; epochs<90000000; epochs++){
        //Obtaining Predicted Values:
            float p_outputs[7];   //Predicted Outputs
            float v[7];
            for(int i=0;i<7;i++){
                v[i] = bias;
                for(int j=0;j<3;j++){
                    v[i]+= inputs[i][j]*weights[j];
                }
                p_outputs[i] = (freud(v[i]));
            }
        //Figuring the cost out
            cost = 0;
            for(int i=0;i<7;i++){
                cost += pow((p_outputs[i]-act_outputs[i]), 2); 
            }
            cost/=7;
            if(cost<=0.00013)
                break;
        //Correcting Weights
            for(int i=0;i<3;i++){
                float delphi = 0;
                for(int j=0;j<7;j++){
                    delphi += (freud(v[j])- act_outputs[j])*d_freud(v[j])*inputs[j][i];
                }
                delphi*= 2*eta/7;

                weights[i] = weights[i] - delphi;
            }
        
        //Correcting the bias
            float delphib;
            for(int j=0;j<7;j++){
                    delphib += (freud(v[j])- act_outputs[j])*d_freud(v[j]);
                }
            delphib*= 2*eta/7;
            bias -= delphib;
        //  cout << cost << endl;
        //  cout << "The weights are :" << weights[0]<< " "<<weights[1]<< " "<<weights[2]<< endl;
            
    }
    cout << "The weights are :" << weights[0]<< " "<<weights[1]<< " "<<weights[2]<< endl;
    cout <<"The cost is "<< cost << "And the bias is "<<bias<< endl;
    int new_input[] = {1, 1, 1};
    float new_out, vn = 0;
    for(int i=0;i<3;i++){
        vn+=new_input[i]*weights[i];
    }
    cout << (freud(vn)) << endl;
    int new_input2[] = {1, 0, 1};
    float new_out2, vn2 = 0;
    for(int i=0;i<3;i++){
        vn2+=new_input2[i]*weights[i];
    }
    cout << (freud(vn2)) << endl;
    int new_input3[] = {1, 0, 0};
    float new_out3, vn3 = 0;
    for(int i=0;i<3;i++){
        vn3+=new_input3[i]*weights[i];
    }
    cout << (freud(vn3)) << endl;
    return 0;
}