#include "stdafx.h"
#include "NeuralNetwork.h"

/// 
/// @brief default constructor
///
/// sets up the neuron network.
/// 
/// @note assumes that its atleast a 2-layer NN
/// 
/// @param a_neuronPerEachLayerList memory address of 
///		vector containing the number of neuron each layer
///
NeuralNetwork::NeuralNetwork(const std::vector<int>& a_neuronPerEachLayerList)
{
	assert(a_neuronPerEachLayerList.size() == 3);

	// setting up input layer
	m_neuronLayers.push_back(new NeuralNetworkLayer(ENUM_NeuronLayerType::m_inputLayer,
													a_neuronPerEachLayerList.front()));

	// setting up hidden layers
	for(unsigned i = 1; i < a_neuronPerEachLayerList.size() - 1; ++i)
	{
		m_neuronLayers.push_back(new NeuralNetworkLayer(ENUM_NeuronLayerType::m_hiddenLayer,
														a_neuronPerEachLayerList.at(i)));
	}

	// setting up output layer
	m_neuronLayers.push_back(new NeuralNetworkLayer(ENUM_NeuronLayerType::m_outputLayer,
													a_neuronPerEachLayerList.front()));
}

NeuralNetwork::~NeuralNetwork()
{
	for(unsigned i = 0; i < m_neuronLayers.size(); ++i)
	{
		delete m_neuronLayers[ i ];
	}

	//clearing the m_neuronLayers vector
	m_neuronLayers.clear();
}

///
/// @brief Initiales the parameters by calling the InitializeRandomParameters function for each layer
///
void NeuralNetwork::InitialParameters()
{
	for(unsigned i = 1; i < m_neuronLayers.size(); ++i)
	{
		m_neuronLayers[ i ]->InitializeRandomParameters(m_neuronLayers[ i - 1 ]->GetLayerWidth());
	}
}

///
/// @brief calls forward propagation on each layer
///  
/// @param a_ActivationFuncPerLayerList memory address of 
///		vector containing the activation funciton to call on 
///		 of neuron network layer
/// 
/// @note the first element of a_ActivationFuncPerLayerList should be 
///		AF::ENUM_ActiFunc::m_none as no forward propagation is done in 
///		input layer
/// 
void NeuralNetwork::ForwardPropagation(const std::vector<AF::ENUM_ActiFunc>& a_ActivationFuncPerLayerList)
{
	// confirming that the parameters contains equal number of activation function as
	// the number of layers
	assert(a_ActivationFuncPerLayerList.size() == m_neuronLayers.size());
	// confirming that the first element is AF::ENUM_ActiFunc::m_none
	assert(a_ActivationFuncPerLayerList[ 0 ] == AF::ENUM_ActiFunc::m_none);

	// calling the forward propagation on each layer
	// excluding the input layer
	for(unsigned i = 1; i < m_neuronLayers.size(); ++i)
	{
		m_neuronLayers[ i ]->ForwardPropagation(( m_neuronLayers[ i - 1 ] )->GetLayerNeuronList(),
												a_ActivationFuncPerLayerList[ i ]);
	}
}
