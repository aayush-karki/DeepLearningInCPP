#pragma once
#include "Neuron.h"
#include "InputNeuron.h"
#include "OutputNeuron.h"

/// @brief Lists the type of neuron layer there can be  
enum class ENUM_NeuronLayerType
{
	m_inputLayer,
	m_outputLayer,
	m_hiddenLayer,
};

class NeuralNetworkLayer
{
	// ===================== Public Member Function =================
public:
	NeuralNetworkLayer(ENUM_NeuronLayerType a_layerType = ENUM_NeuronLayerType::m_inputLayer,
					   unsigned a_TotalNeuralNum = 1); // constructor
	~NeuralNetworkLayer(); // destructor
	
	const unsigned GetLayerWidth() const ; // getter funciton 
	const std::vector<Neuron*>& GetLayerNeuronList() const; // getter funciton
	
	void InitializeRandomParameters(unsigned a_previousLayerWidth); // calls the initialize parameter for each neuron
	void ForwardPropagation(const std::vector<Neuron*>& a_prevNNLayerNeurons,
							AF::ENUM_ActiFunc a_activationFunc);

	// ===================== Private Data Member ====================
private:
	std::vector<Neuron*> m_layerNeuronList;
	ENUM_NeuronLayerType m_layerType;

	const unsigned m_layerWidth; // number of neuron in the layer
};

/// 
/// @brief getter function to get the layer's width  
/// 
/// @return number of neuron in the layer
/// 
inline const unsigned NeuralNetworkLayer::GetLayerWidth() cosnt
{
	return m_layerWidth;
}

/// 
/// @brief getter function to get the address to list that points to layer's neurons 
/// 
/// @return address to list that points to layer's neurons 
/// 
inline const std::vector<Neuron*>& NeuralNetworkLayer::GetLayerNeuronList() const
{
	return m_layerNeuronList;
}

