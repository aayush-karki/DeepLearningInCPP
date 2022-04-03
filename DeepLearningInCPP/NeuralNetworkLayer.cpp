#include "stdafx.h"
#include "NeuralNetworkLayer.h"

///
/// @brief constructor
/// 
/// dynamicaly allocates the neuron
/// 
/// @param a_layerType 
/// @param a_TotalNeuralNum 
/// 
NeuralNetworkLayer::NeuralNetworkLayer(ENUM_NeuronLayerType a_layerType, unsigned a_TotalNeuralNum):
	m_layerType(a_layerType), m_layerWidth(a_TotalNeuralNum)
{
	// dynamically allocating neurons

	if(a_layerType == ENUM_NeuronLayerType::m_inputLayer)
	{
		for(unsigned i = 0; i < a_TotalNeuralNum; ++i)
		{
			m_layerNeuronList.push_back(new InputNeuron);
		}
	}
	else if (a_layerType == ENUM_NeuronLayerType::m_outputLayer)
	{
		for(unsigned i = 0; i < a_TotalNeuralNum; ++i)
		{
			m_layerNeuronList.push_back(new OutputNeuron);
		}
	}
	else
	{
		for(unsigned i = 0; i < a_TotalNeuralNum; ++i)
		{
			m_layerNeuronList.push_back(new Neuron);
		}
	}
}

NeuralNetworkLayer::~NeuralNetworkLayer()
{
	// deallocating the vectors
	for(unsigned i = 0; i < m_layerNeuronList.size(); ++i)
	{
		delete m_layerNeuronList[ i ];
	}

	m_layerNeuronList.clear(); // clearling the vector list itself
}

///
/// @brief calls the initialize random parameter funciton of each neuron
///
void NeuralNetworkLayer::InitializeRandomParameters(unsigned a_previousLayerWidth)
{
	for(unsigned i = 0; i < m_layerNeuronList.size(); ++i)
	{
		m_layerNeuronList[ i ]->InitializeRandomParameters(a_previousLayerWidth);
	}
}


///
/// @brief Calls forward Propagation on each of its neuron 
///
/// @param a_prevNNLayerNeurons memory address to vector containing
///		 the pointer to neurons in previous layer
/// @param a_activationFunc  activatoin function to call
///
void NeuralNetworkLayer::ForwardPropagation(const std::vector<Neuron*>& a_prevNNLayerNeurons,
											AF::ENUM_ActiFunc a_activationFunc)
{
	// calling the linear-activation function for each neuron
	for(unsigned i = 0; i < m_layerNeuronList.size(); ++i)
	{
		m_layerNeuronList[ i ]->LinerActivation(a_prevNNLayerNeurons, 
												a_activationFunc);
	}
}
