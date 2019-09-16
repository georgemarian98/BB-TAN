#ifndef NEURAL_NETWORK_H_INCLUDED
#define NEURAL_NETWORK_H_INCLUDED
#include"Perceptron.h"
class NeuralNetwork{
private:
    int noInputs;
    int noHidden;
    int noOutputs;
    Matrice wH;
    Matrice wO;
    Matrice biasH;
    Matrice biasO;
public:
    NeuralNetwork(int noInputs, int noHidden, int noOutputs );
    float* feedfoward(float* intrari);
    float** train();
    void afisare();
};


#endif // NEURAL_NETWORK_H_INCLUDED
