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
NeuralNetwork::NeuralNetwork( const std::vector<int>& a_neuronPerEachLayerList ) :
	m_dataSet( nullptr ), m_actualLabel(nullptr), m_cost(0.0)
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
													a_neuronPerEachLayerList.back()));
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
/// @brief sets the activaiton fucition that each layer uses
/// @param a_ActivationFuncPerLayerList memory address of 
///		vector containing the activation funciton to call on 
///		 of neuron network layer
/// 
void NeuralNetwork::SetActivaitonFunciton( const std::vector<AF::ENUM_ActiFunc>& a_ActivationFuncPerLayerList )
{
	// confirming that the parameters contains equal number of activation function as
	// the number of layers
	assert( a_ActivationFuncPerLayerList.size() == m_neuronLayers.size() );
	// confirming that the first element is AF::ENUM_ActiFunc::m_none
	assert( a_ActivationFuncPerLayerList[ 0 ] == AF::ENUM_ActiFunc::m_none );

	// setitng  the activaiton function for each layer 
	for( unsigned currNeuronLayerIdx = 0; currNeuronLayerIdx < m_neuronLayers.size(); ++currNeuronLayerIdx )
	{
		m_neuronLayers.at( currNeuronLayerIdx )->SetActivaitonFunciton( a_ActivationFuncPerLayerList.at( currNeuronLayerIdx ) );
	}
}

/// 
/// @brief setter function
/// @param a_dataSet pointer that points to the dataset; 
///			dataset is vector of vector of uint8_t
/// 
void NeuralNetwork::SetDataSet( std::vector<std::vector<uint8_t>>* a_dataSet )
{
	m_dataSet = a_dataSet;
}

///
/// @brief calls forward propagation on each layer
///  
/// @note the first element of a_ActivationFuncPerLayerList should be 
///		AF::ENUM_ActiFunc::m_none as no forward propagation is done in 
///		input layer
/// 
void NeuralNetwork::ForwardPropagation()
{
	// calling the forward propagation on each hidden layer
	for(unsigned i = 1; i < m_neuronLayers.size() - 1; ++i)
	{
		m_neuronLayers[ i ]->ForwardPropagation(( m_neuronLayers[ i - 1 ] )->GetLayerNeuronList());
	}

	// calling the forward propagation on the output layer
	// it saves the neuron with the largest activaiton 
	// getting the output neurons 
	NeuralNetworkLayer* outputLayer = m_neuronLayers.back();
	std::vector<Neuron*> outputNeuralList = outputLayer->GetLayerNeuronList();
	Neuron* largestActivatedNeuron = *(outputNeuralList.begin());

	for( unsigned neuronIdx = 0; neuronIdx < outputNeuralList.size() - 1; ++neuronIdx ) 
	{
		outputNeuralList.at( neuronIdx )->LinerActivation( m_neuronLayers[ m_neuronLayers.size() - 2 ]->GetLayerNeuronList());

		// checking and saving the neuron with the largest activation value
		if( outputNeuralList.at( neuronIdx )->GetActivationValue() > largestActivatedNeuron->GetActivationValue() )
		{
			largestActivatedNeuron = outputNeuralList.at( neuronIdx );
		}
	}

	// caching the neuron with the largest activation value
	m_cachedPredictedNeuron.push_back( largestActivatedNeuron );

}

/// 
/// @brief  calculates the cost/ loss function
/// 
void NeuralNetwork::CalculateCost()
{
	// checking that the number matches
	assert( m_cachedPredictedNeuron.size() == m_actualLabel->size() );

	// calculating the cost
	m_cost = 0.0;
	
	// for each predicted neuron summing the loss error
	for( unsigned idx = 0; idx < m_cachedPredictedNeuron.size(); ++idx )
	{
		m_cost += m_cachedPredictedNeuron.at( idx )->CalculateLoss( m_actualLabel->at(idx));
	}

	m_cost /= ( m_actualLabel->size() );
	m_cost *= -1;
}

/// 
/// @brief Gets the output nueron with the largest activation
/// 
/// @return output nueron with the largest activation
/// 
Neuron* NeuralNetwork::GetPredictedNeuron() const
{
	// getting the output neurons 
	NeuralNetworkLayer* outputLayer = m_neuronLayers.back();
	std::vector<Neuron*> outputNeuralList = outputLayer->GetLayerNeuronList();

	// finding the largest activation
	std::vector<Neuron*>::iterator currIte = outputNeuralList.begin();
	Neuron* largestActivatedNeuron = *currIte;

	while( currIte != outputNeuralList.end() )
	{
		if( ( *currIte )->GetActivationValue() > largestActivatedNeuron->GetActivationValue() )
		{
			largestActivatedNeuron = *currIte;
		}
	}

	return largestActivatedNeuron;
}
