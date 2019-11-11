#include "ProcessLIB.h"

//CLASS NEURON
    class neuron{
        vector<float> weights;
        float bias;
        float cost;
        unsigned int w_width;
        unsigned int index_in_layer;
        float eta; //learning rate
        int epochs;

        neuron_layer *nextL;

        float phi(float x);
        float d_phi(float x);
        //Perceptron
        float calcCost(vector<float> x,vector<float> y);
        // Network
            //float del()

    public:
        neuron(int input_cardinality);
        float output(vector<float> X);
        float findOut(vector<float> F){
            return phi(output(F));
        }
        vector<float> output_set(vector<vector<float>> X);  
        vector<float> getWeightedSum(vector<vector<float>> sinputs); 
        void perceptron_learnfrom(vector<vector<float>> sanple_inputs, vector<float> desired_out);
        void perceptron_stoch_learnfrom(vector<vector<float>> sanple_inputs, vector<float> desired_out);
    };

    float neuron::calcCost(vector<float> x, vector<float> y){
        //Calculating the MSE for x and y
        float c = 0;
        for(int i=0;i<x.size();i++){
            c+=pow(x[i]-y[i], 2);
        }
        c/=x.size();
        return c;
    }

    vector<float> neuron::getWeightedSum(vector<vector<float>> sinputs){
        vector<float> v;
        for(int i=0;i<sinputs.size();i++){
            v.push_back(output(sinputs[i]));
        }
        return v;
    }

    neuron::neuron(int input_cardinality){
        int n = input_cardinality;
        w_width = n;
        for(int i=0;i<n;i++){
            weights.push_back(rand()%2+0.5);
        }
        bias = rand()%2+0.5;
        eta = 0.00001;
        epochs = 90000;
    }

    float neuron::phi(float x){
        return (1+tanh(x))/2;
    }

    float neuron::d_phi(float x){
        return pow(cosh(x), -2)/2;
    }

    float neuron::output(vector<float> X){
        int n = weights.size();
        float o = bias;
        for(int i=0;i<n;i++){
            o += X[i]*weights[i];
        }

        return o;
    }



    vector<float> neuron::output_set(vector<vector<float>> X){
        vector<float> out;
        for(int i=0;i<X.size();i++){
            out.push_back(phi(output(X[i])));
        }
        return out;
    }

    void neuron::perceptron_learnfrom(vector<vector<float>> sample_inputs, vector<float> desired_out){
        vector<float> pre_out = output_set(sample_inputs);
        cost  = calcCost(pre_out, desired_out);
        int datasize = sample_inputs.size();
        vector<float> v = getWeightedSum(sample_inputs);
        for(int i=0;i<epochs, cost>=0.001;i++){
            //Correcting the Weights
            for(int i=0;i<w_width;i++){
                float del = 0;
                for(int j=0;j<datasize;j++)
                    del+=(phi(v[j]) - desired_out[j])*d_phi(v[j])*sample_inputs[j][i];
                del*= 2*eta/datasize;
                weights[i] -= del;
            }

            //Correcting the bias
            float delphib;
            for(int j=0;j<datasize;j++){
                delphib += (phi(pre_out[j])- desired_out[j])*d_phi(v[j]);
            }
            delphib*= 2*eta/datasize;
            bias -= delphib;

            //Calculating the new cost << Calculating the new predicted outputs.
            pre_out  = output_set(sample_inputs);
            cost = calcCost(pre_out, desired_out);
        }
    }



//..

//CLASS NEURON LAYER
    class neuron_layer{ 
        vector<neuron> neurons;
        unsigned int layer_size;
        vector<float> input_stream;
        vector<float> output_stream;
        neuron_layer *next, *prev;
    public:
        neuron_layer(int size, neuron_layer *p,neuron_layer *n = NULL);
        void learn(vector<float> inp, vector<float> des_out);
        vector<float> getOutput(vector<float> inp);
        void setNext(neuron_layer *p){
            next = p;
        }
        neuron_layer *getNext(){
            return next;
        }
        void setPrec(neuron_layer *p){
            prev = p;
        }
        vector<float> get_output(vector<float> input);
        neuron_layer *getPrev(){
            return prev;
        }
        vector<float> getDel(vector<float> a, vector<float> z, vector<float> desired_output = {});
    };

    neuron_layer::neuron_layer(int size, neuron_layer *p,neuron_layer *n = NULL){
       // assert(size>0); || assert(size>-1)
        layer_size = size;
        prev=p;
        next = n;
    }

    vector<float> neuron_layer::getDel(vector<float> a, vector<float> z, vector<float> desired_output = {}){
        // del(L) = nabla<C, a>_Hamadard_phi'(z)
        // del(l!=L) = (w(l+1).T)Xdel(l+1)_Hamadard_phi'(z)
        vector<float> d;
        if(this->next!=NULL){
            // del(l!=L) = (w(l+1).T)Xdel(l+1)_Hamadard_phi'(z)
        }
        else{
            //del(L) = nabla<C, a>_Hamadard_phi'(z)
        }
        return d;
    }

// Class ANN
    class ANN{
        neuron_layer *inputL;
        neuron_layer *outputL;//The hidden layers will be pointed to by others

        unsigned int depth;
    public:
        ANN(int n);
        vector<float> getOutput(vector<float> input);
        vector<float> seekInput(vector<float> input){
            return input;
        }
        vector<float> seekExpectedOutput(vector<float> output){
            return output;
        }
        void learn(vector<vector<float>> input, vector<vector<float>> desout);
    };

    ANN::ANN(int n){
        assert(n>0);
        depth = n;
        //Creating n layers - the first as the input layer and the last as the output layer.
        neuron_layer *current=NULL, *temp;
        for(int i=0;i<n;i++){
            if(i==0){
                inputL = new neuron_layer(n, current);
                current = inputL;
            }
            else{
                temp = new neuron_layer(n-i, current);
                current->setNext(temp);
                current = current->getNext();
                if(i==n-1){
                    outputL = current;
                    outputL->setNext(NULL);
                }
            }
        }
    }

    void ANN::learn(vector<vector<float>> input, vector<vector<float>> desout){
        //Getting the computed output


    }

    vector<float> ANN::getOutput(vector<float> input){
        static neuron_layer *current = inputL;
        

    }
