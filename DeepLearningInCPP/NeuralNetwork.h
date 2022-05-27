#pragma once
#include "NeuralNetworkLayer.h"

class NeuralNetwork
{
	// ===================== Public Member Function =================
public:
	NeuralNetwork(const std::vector<int>& a_neuronPerEachLayerList); // default constructor
	~NeuralNetwork(); // desturctor	

	// setter function
	void SetActivaitonFunciton( const std::vector<AF::ENUM_ActiFunc>& a_ActivationFuncPerLayerList );
	void SetDataSet( std::vector<std::vector<uint8_t>>* a_dataSet );


	// initializing neuron
	 void InitialParameters(); 
	void ForwardPropagation(); // does forward propagation
	std::vector<NeuralNetworkLayer*>& GetNeuronLayers();
	
	void CalculateCost();

	Neuron* GetPredictedNeuron() const;

	// ===================== Private Data Member ====================
private:
	std::vector<NeuralNetworkLayer*> m_neuronLayers;
	
	std::vector<uint8_t>* m_actualLabel; // pointer to the vector containing the actual label
	std::vector<std::vector<uint8_t>>* m_dataSet; // pointer to the vector containg the train/test set
	std::vector<Neuron*> m_cachedPredictedNeuron;
	long double m_cost;

};

inline std::vector<NeuralNetworkLayer*>& NeuralNetwork::GetNeuronLayers() 
{
	return m_neuronLayers;
}