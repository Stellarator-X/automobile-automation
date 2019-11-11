#include "ProcessLIB.h"
#include "FH.h"
//Calculus
    float phi(float x)//activation function
    {
        return (1 + tanh(x))/2;
    }

    float d_phi(float x)//derivative of activation function
    {
        return 0.5*(pow(cosh(x), -2));
    }

    vector<float> phi(vector<float> x){
        vector<float> result;
        int n = x.size();
        for(int i=0;i<n;i++)
            result.push_back(phi(x[i]));
        return result;
    }

    vector<float> d_phi(vector<float> x){
        vector<float> result;
        int n = x.size();
        for(int i=0;i<n;i++)
            result.push_back(d_phi(x[i]));
        return result;
    }



//Network - Virtual
    class neural_net{
        layer *input_layer;
        layer *output_layer;
        vector<vector<float>> del;//2D as everyu neuron has a unique del

        string netDirectory;
        int depth;
    public:
        neural_net(int n, vector<int> layerSizes, string s);//Constructor with layer-depth

        vector<float> getOutput(vector<float> input);
        void calc_del(vector<float> input, vector<float> output);
        vector<vector<float>> getDel();
        void stoch_learn_from(vector<vector<float>> inputs, vector<vector<float>> outputs);
        layer *getLayerNo(int x);
        void learn_from(vector<vector<float>> inputs, vector<vector<float>> outputs);
        float getCost(vector<vector<float>> inputs, vector<vector<float>> outputs);

        void setLearnedWeights();//Virtual

    };

//Layer - Virtual
 class layer{
        vector<neuron> neurons;
        layer *next, *prev;
       // neural_net *thisNetwork;
        vector<float> Z;
        int size;
    public:
        
        layer(int n);//, neural_net *N);//Constructor
        
        layer* getNext(){
            return next;
        }
        vector<float> giveZ(){
            return Z;
        }
        vector<float> returnDel();
        vector<float> getZ(vector<float> input);
        void setNext(layer *n){
            next=n;
        }
        layer* getPrev(){
            return prev;
        }
        vector<neuron> getNeurons(){
            return neurons;
        }
        vector<vector<float>> getWeightMatrix();
        void setPrev(layer *n){
            prev=n;
        }
        int getSize(){
            return size;
        }
        vector<float> getOutput(vector<float> input);
        vector<float> getDel(vector<float> delnxt);
        void setWeights(vector<vector<float>> ww);
    };
//Neuron  - Virtual
    class neuron{
        int n_inputs;
        float z;//weighted_input_stream;
        vector<float> weights;
        vector<float> inputStream;
        float bias;
        float current_del;
        vector<float> d;

        layer *thisLayer;
    public:
        neuron(int n, layer *l);//Constructor
        float getZ(vector<float> input);
        vector<float> getWeights(){
            return weights;
        }
        float getOutput(vector<float> input);
        void setWeight(int i, float n){
            assert(weights.size()>i+1);
            weights[i] = n;
        }
        void setWeights(vector<float> w){
            weights = w;
        }
        float getDel(){
            return current_del;
        }

        vector<float> getInputs(){
            return inputStream;
        }
        void setDel(float x){
            current_del=x;
        }
    };
//Network - Function defs
    neural_net::neural_net(int n, vector<int> layerSizes, string s){//n-> no of layers, layerSizes
        depth = n;
        assert(n>=1);
        int it = 0;//iterator through layerSizes
        input_layer = new layer(layerSizes[it++]);//, this);
        layer *current = input_layer;
        while(current->getSize()!=1){
            current->setNext(new layer(layerSizes[it++]));  //, this));
            current->getNext()->setPrev(current);
            current = current->getNext();
        }
        output_layer = current;
        netDirectory = s;    
    }

    layer* neural_net::getLayerNo(int x){
        layer *curr = input_layer;
        x--;
        while(x--){
            curr=curr->getNext();
        }
        return curr;
    }



//Layer - Function defs
    layer::layer(int n){      //}, neural_net *N){            
        size = n;
        for(int i=0;i<n;i++){
            neurons.push_back(neuron(n+1, this));
        }
     //   thisNetwork = N;
        next = NULL;
        prev = NULL;
       // thisNetwork = N;
    }

    void layer::setWeights(vector<vector<float>> ww){
        for(int i=0;i<size;i++)
            neurons[i].setWeights(ww[i]);
    }

    vector<vector<float>> layer::getWeightMatrix(){
        vector<vector<float>> result;
        for(int i=0;i<size;i++){
            result.push_back(neurons[i].getWeights());        }
        return result;
    }

    vector<float> layer::returnDel(){
        vector<float> result;
        for(neuron n:neurons){
            result.push_back(n.getDel());
        }
        return result;
    }

    vector<float> layer::getDel(vector<float> delnxt){
        assert(this->getNext()!=NULL);
        vector<vector<float>> result;
        vector<vector<float>> dellp1 = convert_to_2d(delnxt);
        vector<vector<float>> wlp1T = Transpose(next->getWeightMatrix());
        vector<vector<float>> dphi = convert_to_2d(d_phi(giveZ()));
        //result = {w(l+1).T X del(l+1)}.h.d_phi(z(l))
        result = matrixmult_hamadard(matrixmult(wlp1T, dellp1),dphi);
        assert(result.size()==1);
        vector<float> thisdel = result[0];
        for(int i=0;i<size;i++){
            neurons[i].setDel(thisdel[i]);
        }
        return thisdel;
    }

    vector<float> layer::getOutput(vector<float> input){
        vector<float> temp;
        for(int i=0;i<size;i++){
            temp.push_back(neurons[i].getOutput(input));
        }
        return temp;
    }

    vector<float> layer::getZ(vector<float> input){
        vector<float> result;
        for(int i=0;i<size;i++)
            result.push_back(neurons[i].getZ(input));
        Z = result;
        return result;
    }

//Neuron - Function defs
    neuron::neuron(int n, layer *l){
        n_inputs = n;
        for(int i=0;i<n;i++)
            weights.push_back(rand()%2+0.4);
        bias = rand()%2+0.4;
        thisLayer = l;
    }

    float neuron::getOutput(vector<float> input){
        return phi(getZ(input));
    }
    float neuron::getZ(vector<float> input){
        inputStream = input;
        float result = bias;
        
        for(int i=0;i<n_inputs;i++)
            result += weights[i]*input[i];
        z = result;
        return result;
    }

        vector<vector<float>> neural_net::getDel(){
        vector<vector<float>> result;
        layer *curr = input_layer;
        while(curr!=NULL){
            result.push_back(curr->returnDel());
            curr= curr->getNext();
        }
        return result;
    }

    vector<float> neural_net::getOutput(vector<float> input){
        layer *current = input_layer;
        vector<float> buffer = input;
        while(current!=output_layer){
            buffer = current->getOutput(buffer);
            current = current->getNext();
        }
        return output_layer->getOutput(buffer);
    }

    void neural_net::calc_del(vector<float> input, vector<float> output){
        vector<float> pred_output;
        pred_output = getOutput(input);
        
        //Need to initialise every input stream to each neuron => we need the neuron to store an input stream as well.
        //Can be done inside getOutput
        vector<float> del; //Del for the output layer(initially)
        del  = diff(pred_output,output); //ergo, we shall assume the cost func to be MS(~y - y)
        del = matrixmult(convert_to_2d(del), convert_to_2d(output_layer->getZ(input)))[0];

        layer *current = output_layer->getNext();
        while(current!=input_layer){
            del = current->getDel(del);
            current->setNext(current);
        }
    }

    float neural_net::getCost(vector<vector<float>> inputs, vector<vector<float>> outputs){
        float result =0.0f;
        for(auto const& i : combine(inputs, outputs)){
            vector<float> input;
            vector<float> output;
            boost::tie(input, output) = i;
            vector<float> predout = getOutput(input);
            result+=MSE(predout, output);
        }
        result/=inputs.size();
        return result;
    }

    void neural_net::stoch_learn_from(vector<vector<float>> inputs, vector<vector<float>> outputs){//
        //Using Stochastic Gradient Descent
        vector<pair<vector<float>, vector<float>>> dataset;
        for(int i=0;i<inputs.size();i++){
            dataset.push_back(make_pair(inputs[i], outputs[i]));
        }
        static size_t used = 0;
        if(!used);
        FYShuffle(dataset.begin(), dataset.end());
        vector<vector<float>> inpset;
        vector<vector<float>> outset;
        for(int i=0;i<inputs.size(); i++){
            inpset.push_back(dataset[i].first);
            outset.push_back(dataset[i].second);
        }
        
        int setsize = inpset.size()/20;
        int maxit = 20*setsize;
        
        auto starti = inpset.begin();
        auto endi = starti;
        std::advance(endi, setsize);
        vector<vector<float>> inpsubset;
        copy(starti, endi, back_inserter(inpsubset));
        
        auto starto = outset.begin();
        auto endo = starto;
        std::advance(endo, setsize);
        vector<vector<float>> outsubset;
        copy(starto, endo, back_inserter(outsubset));

        while(used<maxit){
            learn_from(inpsubset, outsubset);
            starti=endi;
            std::advance(endi, setsize);
            starto = endo;
            std::advance(endo, setsize);
            used+=setsize;  
        }
    }

    void neural_net::learn_from(vector<vector<float>> inputs, vector<vector<float>> outputs){
        int epochs = 300000;
        const int eta = 0.008;

        float Cost = getCost(inputs, outputs);
        
        while((epochs--)&&(Cost>0.001)){ //Iterating throughout epochs or till Cost is reasonably minimised
            
            vector < vector< float > >  DEL;
            vector < vector < vector< float > > > DCbDW;
            layer *curr = input_layer;
            while(curr!=NULL){//Initialising all dels to zero first
                vector<float> dell;
                for(neuron n: curr->getNeurons()){
                    dell.push_back(0.0f);
                }
                DEL.push_back(dell);
                curr = curr->getNext();
            }

            //Initialising all cost derivatives to zero
            layer* lcur = input_layer;
            while(lcur!=NULL){
                vector<vector<float>> v2;
                for(int i=0;i<lcur->getNeurons().size();i++){
                    vector<float> v1(lcur->getNeurons()[i].getInputs().size());
                    v2.push_back(v1);
                }
                DCbDW.push_back(v2);
            }

            for(int i=0;i<inputs.size();i++){//Calculating the dels and iteratively adding to take an average later
                calc_del(inputs[i], outputs[i]);
                //Filling the DEL Matrix
                vector<vector<float>> newdel = getDel();
                
                //Filling the DCbDW matrix - incorrect approach - requires init to 0 first
                layer *l = input_layer;
                for(int i=0;i<newdel.size();i++, l = l->getNext()){
                    for(int j=0;j<newdel[i].size();j++){
                        for(int k=0;k<DCbDW[i][j].size();k++){
                            DCbDW[i][j][k]+=(l->getNeurons()[j].getInputs()[k])*newdel[i][j];
                        }
                    }
                }
                DEL = matrix_add(DEL, newdel);

            }
            DEL = matrix_divelts(DEL, inputs.size());
            DCbDW = TriMatrix_divelts(DCbDW, inputs.size());

            
            //Correcting the weights
            layer *l = input_layer;
            for(int i=0;i<DCbDW.size();i++, l = l->getNext()){
                for(int j=0;j<DCbDW[i].size();j++){
                    for(int k=0;k<DCbDW[i][j].size();k++){
                        l->getNeurons()[j].setWeight(k, l->getNeurons()[j].getWeights()[k] - eta*DCbDW[i][j][k]);
                    }
                }
            }

        }
        //Now that weights have been corrected - We need to modify the file containing the weights - or in this case, create the file and add the weights
        
        chdir(netDirectory.c_str());
        layer *lcur = input_layer;
        for(int i=0;i<depth;i++, lcur = lcur->getNext()){
            vector<vector<float>> n_weights;
            for(int j=0;j<lcur->getNeurons().size();j++){
                n_weights.push_back(lcur->getNeurons()[j].getWeights());
            }
            char *name = "Layer";
            name[5] = i;    //Assuming depth <= 10 
            name[6] = '\0';
            modify_csv_file(name, n_weights);
        }
    }

    void neural_net::setLearnedWeights(){
        chdir(netDirectory.c_str());
        string  fs = "Layer";
        //Continuing assumption about network depth
        layer *lcur = input_layer;
        //int i, j, k;
        int i=0;
         while(lcur!=NULL){
            vector<vector<float>> weightsofl;
            weightsofl = get2dvec(fs+(char)('0'+i));
            i++;
            lcur->setWeights(weightsofl);
            weightsofl.clear();
        }
    }
