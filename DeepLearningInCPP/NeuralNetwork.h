#pragma once
#include "NeuralNetworkLayer.h"

class NeuralNetwork
{
	// ===================== Public Member Function =================
public:
	NeuralNetwork( unsigned a_numData, const std::vector<int>& a_neuronPerEachLayerList); // constructor
	~NeuralNetwork(); // desturctor	

	// setter function
	void SetActivaitonFunciton( const std::vector<AF::ENUM_ActiFunc>& a_ActivationFuncPerLayerList );
	void SetDataSet( std::vector<std::vector<uint8_t>*>* a_dataSet );
	void SetDataLabel( std::vector<uint8_t>* a_dataLabel );

	// initializing neuron
	void InitialParameters(); 
	void ForwardPropagation(); // does forward propagation
	std::vector<NeuralNetworkLayer*>& GetNeuronLayers();
	
	void CalculateCost();

	Neuron* GetPredictedNeuron() const;
	void CacheAllPredictedNeuron();

	// ===================== Private Data Member ====================
private:
	std::vector<NeuralNetworkLayer*> m_neuronLayers;
	
	std::vector<uint8_t>* m_actualLabel; // pointer to the vector containing the actual label
	std::vector<std::vector<uint8_t>*>* m_dataSet; // pointer to the vector containg the train/test set
	std::vector<Neuron*> m_cachedPredictedNeuron;
	long double m_cost;

};

/// 
/// @brief Getter function to ge the vector containing the neuron layer
///
inline std::vector<NeuralNetworkLayer*>& NeuralNetwork::GetNeuronLayers() 
{
	return m_neuronLayers;
}


/// 
/// @brief setter function
/// 
/// SetDataLabel saves the pointer to actual labels
/// 
/// @param a_dataLabel pointer that points to the actual label; 
///			a_dataLabel is vector of uint8_t
/// 
inline void NeuralNetwork::SetDataLabel( std::vector<uint8_t>* a_dataLabel )
{
	m_actualLabel = a_dataLabel;
}
