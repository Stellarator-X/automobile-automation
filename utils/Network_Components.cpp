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

    std::vector<float> phi(std::vector<float> x){
        std::vector<float> result;
        int n = x.size();
        for(int i=0;i<n;i++)
            result.push_back(phi(x[i]));
        return result;
    }

    std::vector<float> d_phi(std::vector<float> x){
        std::vector<float> result;
        int n = x.size();
        for(int i=0;i<n;i++)
            result.push_back(d_phi(x[i]));
        return result;
    }





//Neuron  - Virtual
    class neuron{
        int n_inputs;
        float z;//weighted_input_stream;
        std::vector<float> weights;
        std::vector<float> inputStream;
        float bias;
        int ind;
        float current_del;
        std::vector<float> d;

        //layer *thisLayer;
    public:
        neuron(int n);//Constructor
        float getZ(std::vector<float> input);
        std::vector<float> getWeights(){
            return weights;
        }
        float getOutput(std::vector<float> input);
        void setWeight(int i, float n){
            assert(weights.size()>i);
            weights[i] = n;
        }
        void setWeights(std::vector<float> w){
            weights = w;
        }
        float getDel(){
            return current_del;
        }

        std::vector<float> getInputs(){
            return inputStream;
        }
        void setDel(float x){
            current_del=x;
        }
    };
//Layer - Virtual
 class layer{
        std::vector<neuron> neurons;
        layer *next;
        layer *prev;
       // neural_net *thisNetwork;
        std::vector<float> Z;
        int size;
    public:
        
        layer(int n, layer *p);//, neural_net *N);//Constructor
        
        layer* getNext(){
            return next;
        }
        std::vector<float> giveZ(){
            return Z;
        }
        std::vector<float> returnDel();
        std::vector<float> getZ(std::vector<float> input);
        void setNext(layer *n){
            next=n;
        }
        layer* getPrev(){
            return prev;
        }
        std::vector<neuron> *getNeurons(){
            return &neurons;
        }
        std::vector<std::vector<float>> getWeightMatrix();
        void setPrev(layer *n){
            prev=n;
        }
        int getSize(){
            assert(this!=NULL);
            return this->size;
        }
        std::vector<float> getOutput(std::vector<float> input);
        std::vector<float> getDel(std::vector<float> delnxt);
        void setWeights(std::vector<std::vector<float>> ww);
    };
//Network - Virtual

    class neural_net{
        layer *input_layer;
        layer *output_layer;
        std::vector<std::vector<float>> del;//2D as every neuron has a unique del
        float eta;//Learning Rate
        std::__cxx11::string netDirectory;
        int depth;
    public:
        neural_net(int n, std::vector<int> layerSizes, std::__cxx11::string s, float lr);//Constructor with layer-depth

        std::vector<float> getOutput(std::vector<float> input);
        void calc_del(std::vector<float> input, std::vector<float> output);
        std::vector<std::vector<float>> getDel();
        void stoch_learn_from(std::vector<std::vector<float>> inputs, std::vector<std::vector<float>> outputs);
        layer *getLayerNo(int x);
        void learn_from(std::vector<std::vector<float>> inputs, std::vector<std::vector<float>> outputs);
        float getCost(std::vector<std::vector<float>> inputs, std::vector<std::vector<float>> outputs);

        void setLearnedWeights();

        void Q_Update();//Virtual

    };

//Network - Function defs
    neural_net::neural_net(int n, std::vector<int> layerSizes, std::__cxx11::string s, float lr){
        //n-> no of layers, layerSizes
        eta = lr;
        depth = n;
        assert(n>=1);
        int it = 0;//iterator through layerSizes
        input_layer = new layer(layerSizes[it++], NULL);//, this);
        layer *current = input_layer;
        while(it<n){
            current->setNext(new layer(layerSizes[it++], current));  //, this));
           // current->getNext()->setPrev(current);
            current = current->getNext();
        }
        output_layer = current;
        netDirectory = s;    
        //chdir(netDirectory.c_str());
    }

    layer* neural_net::getLayerNo(int x){
        layer *curr = input_layer;
        x--;
        while(x--){
            curr=curr->getNext();
        }
        return curr;
    }

    std::vector<std::vector<float>> neural_net::getDel(){
        std::vector<std::vector<float>> result;
        layer *curr = input_layer;
        while(curr!=NULL){
            result.push_back(curr->returnDel());
            curr= curr->getNext();
        }
        return result;
    }

    std::vector<float> neural_net::getOutput(std::vector<float> input){
        layer *current = input_layer;
        std::vector<float> buffer = input;
        while(current!=output_layer){
            buffer = current->getOutput(buffer);
            current = current->getNext();
        }
        return output_layer->getOutput(buffer);
    }

    void neural_net::calc_del(std::vector<float> input, std::vector<float> output){
        std::vector<float> pred_output;
        pred_output = getOutput(input);
        
        //Need to initialise every input stream to each neuron => we need the neuron to store an input stream as well.
        //Can be done inside getOutput
        std::vector<float> del; //Del for the output layer(initially)
        del  = diff(pred_output,output); //ergo, we shall assume the cost func to be MS(~y - y)
        del = matrixmult_hamadard(convert_to_2d(del), convert_to_2d(d_phi(output_layer->giveZ())))[0];

        layer *current = output_layer->getPrev();
        while(current!=NULL){
            del = current->getDel(del);
            current = current->getPrev();
        }
    }

    float neural_net::getCost(std::vector<std::vector<float>> inputs, std::vector<std::vector<float>> outputs){
        float result =0.0f;
        for(auto const& i : boost::combine(inputs, outputs)){
            std::vector<float> input;
            std::vector<float> output;
            boost::tie(input, output) = i;
            std::vector<float> predout = getOutput(input);
            result+=MSE(predout, output);
        }
        result/=inputs.size();
        return result;
    }

    void neural_net::stoch_learn_from(std::vector<std::vector<float>> inputs, std::vector<std::vector<float>> outputs){//
        //Using Stochastic Gradient Descent
        std::vector<std::pair<std::vector<float>, std::vector<float>>> dataset;
        for(int i=0;i<inputs.size();i++){
            dataset.push_back(make_pair(inputs[i], outputs[i]));
        }
        static size_t used = 0;
        if(!used);
        FYShuffle(dataset.begin(), dataset.end());
        std::vector<std::vector<float>> inpset;
        std::vector<std::vector<float>> outset;
        for(int i=0;i<inputs.size(); i++){
            inpset.push_back(dataset[i].first);
            outset.push_back(dataset[i].second);
        }
        
        int setsize = inpset.size()/20;
        int maxit = 20*setsize;
        
        auto starti = inpset.begin();
        auto endi = starti;
        std::advance(endi, setsize);
        std::vector<std::vector<float>> inpsubset;
        copy(starti, endi, back_inserter(inpsubset));
        
        auto starto = outset.begin();
        auto endo = starto;
        std::advance(endo, setsize);
        std::vector<std::vector<float>> outsubset;
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

    void neural_net::learn_from(std::vector<std::vector<float>> inputs, std::vector<std::vector<float>> outputs){
        int epochs = 3000;
        static float eta_used = eta;
        //eta += 0.02;

        float Cost = getCost(inputs, outputs);
        int iteration=0;
        while((epochs--)&&(Cost>0.001)){ //Iterating throughout epochs or till Cost is reasonably minimised
            if(iteration%1000==0)
                cout << "Cost in epoch " << iteration << " is " << Cost << endl;    
            iteration++;
            cout <<">"; 
            vector < std::vector< float > >  DEL;
            vector < vector < std::vector< float > > > DCbDW;
            layer *curr = input_layer;
            int i=0;
            while(curr!=NULL){//Initialising all dels to zero first
                std::vector<float> dell;
                for(neuron n: *(curr->getNeurons())){
                    dell.push_back(0.0f);
                }
                DEL.push_back(dell);
                dell.clear();
                curr = curr->getNext();
                i++;
            }
            
            //Initialising all cost derivatives to zero
            layer* lcur = input_layer;
            while(lcur!=NULL){
                std::vector<std::vector<float>> v2;
                for(int i=0;i<(*(lcur->getNeurons())).size();i++){
                    std::vector<float> v1((*(lcur->getNeurons()))[i].getInputs().size());
                    v2.push_back(v1);
                }
                DCbDW.push_back(v2);
                lcur = lcur->getNext();
               
            }
            
            for(int i=0;i<inputs.size();i++){//Calculating the dels and iteratively adding to take an average later
                
                calc_del(inputs[i], outputs[i]);
                //Filling the DEL Matrix
                std::vector<std::vector<float>> newdel = getDel();
                
                //Filling the DCbDW matrix - incorrect approach - requires init to 0 first
                layer *l = input_layer;
                for(int i=0;i<newdel.size();i++, l = l->getNext()){
                    
                    for(int j=0;j<newdel[i].size();j++){
                        for(int k=0;k<DCbDW[i][j].size();k++){
                            DCbDW[i][j][k]+=((*(l->getNeurons()))[j].getInputs()[k])*newdel[i][j];
                        }
                    }
                }
                std::vector<std::vector<float>> temp = matrix_add(DEL, newdel);
                
                DEL = temp;
            }
            
            DEL = matrix_divelts(DEL, inputs.size());
            DCbDW = TriMatrix_divelts(DCbDW, inputs.size());
          //  cout << "\b";   
            
            //Correcting the weights
            layer *l = input_layer;
            for(int i=0;i<DCbDW.size();i++, l = l->getNext()){
                for(int j=0;j<DCbDW[i].size();j++){
                    for(int k=0;k<DCbDW[i][j].size();k++){
                        (*(l->getNeurons()))[j].setWeight(k, (*(l->getNeurons()))[j].getWeights()[k] - eta*DCbDW[i][j][k]*10000);
                    }
                }
            }

            Cost = getCost(inputs, outputs);
        }
        cout << "Final Cost = " << Cost << endl;
        
        //Now that weights have been corrected - We need to modify the file containing the weights - or in this case, create the file and add the weights
        
        chdir(netDirectory.c_str());
        layer *lcur = input_layer;
        for(int i=0;i<depth;i++, lcur = lcur->getNext()){
            std::vector<std::vector<float>> n_weights;
            for(int j=0;j<(*(lcur->getNeurons())).size();j++){
                n_weights.push_back((*(lcur->getNeurons()))[j].getWeights());
            }
            std::__cxx11::string name = "Layer";
            name+= (i+'0');    //Assuming depth <= 10 
            //name[6] = '\0';
            modify_csv_file(name, n_weights);
        }
    }

    void neural_net::setLearnedWeights(){
        chdir(netDirectory.c_str());
        std::__cxx11::string  fs = "Layer";
        //Continuing assumption about network depth
        layer *lcur = input_layer;
        //int i, j, k;
        int i=0;
         while(lcur!=NULL){
            std::vector<std::vector<float>> weightsofl;
            std::__cxx11::string tempfile = fs + (char)('0'+i);
            weightsofl = get2dvec(tempfile);
            i++;
            lcur->setWeights(weightsofl);
            weightsofl.clear();
            cout << "Got one layer \n";
            lcur = lcur->getNext();
        }
    }



//Layer - Function defs
    layer::layer(int n, layer *p){               
        size = n;
        
        prev = p;
        for(int i=0;i<n;i++){
            if(this->getPrev()!=NULL){
                neurons.push_back(neuron(prev->getSize()));
            
            }
            else
            {
                neurons.push_back(neuron(n));
            }
        }

        next = NULL;
    }

    void layer::setWeights(std::vector<std::vector<float>> ww){
        for(int i=0;i<size;i++)
            neurons[i].setWeights(ww[i]);
    }

    std::vector<std::vector<float>> layer::getWeightMatrix(){
        std::vector<std::vector<float>> result;
        for(int i=0;i<size;i++){
            result.push_back(neurons[i].getWeights());        }
        return result;
    }

    std::vector<float> layer::returnDel(){
        std::vector<float> result;
        for(neuron n:neurons){
            result.push_back(n.getDel());
        }
        return result;
    }

    std::vector<float> layer::getDel(std::vector<float> delnxt){
        assert(this->getNext()!=NULL);
        std::vector<std::vector<float>> result;
        
        std::vector<std::vector<float>> dellp1 = convert_to_2d_col(delnxt);
        std::vector<std::vector<float>> wlp1T = Transpose(next->getWeightMatrix());
        std::vector<std::vector<float>> dphi = convert_to_2d(d_phi(giveZ()));
        //result = {w(l+1).T X del(l+1)}.h.d_phi(z(l))
        result = matrixmult_hamadard(col_to_row(matrixmult(wlp1T, dellp1)),dphi);
        assert(result.size()==1);
        std::vector<float> thisdel = result[0];
        for(int i=0;i<size;i++){
            neurons[i].setDel(thisdel[i]);
        }
        return thisdel;
    }

    std::vector<float> layer::getOutput(std::vector<float> input){
        std::vector<float> temp;
        for(int i=0;i<size;i++){
            temp.push_back(neurons[i].getOutput(input));
        }
        getZ(input);
        return temp;
    }

    std::vector<float> layer::getZ(std::vector<float> input){
        std::vector<float> result;
        for(int i=0;i<size;i++)
            result.push_back(neurons[i].getZ(input));
        Z = result;
        return result;
    }

//Neuron - Function defs
    neuron::neuron(int n){
        static int neurnum = 0;
        ind = neurnum++;
        n_inputs = n;
        for(int i=0;i<n;i++)
            weights.push_back((rand()%5+0.4)/(rand()%3+0.6));
        bias = rand()%2+0.4;

    }

    float neuron::getOutput(std::vector<float> input){
        return phi(getZ(input));
    }
    float neuron::getZ(std::vector<float> input){
        
        assert(input.size()==n_inputs);
        
        inputStream = input;
        float result = bias;


        for(int i=0;i<n_inputs;i++)
            result += weights[i]*input[i];
        z = result;
        return result;
    }

    