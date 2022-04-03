#include "stdafx.h"
#include "Neuron.h"
#include "RandomNumGenerator.h"

/// 
/// @public
/// @brief Initializes the parameters weight to random 
///		double while normalizing it
///
void Neuron::InitializeRandomParameters(unsigned a_previousLayerWidth)
{
	for(unsigned i = 0; i < a_previousLayerWidth; ++i)
	{
		m_weightList.push_back(RandomNumGenerator::GetRandomNumber());
	}
	m_bias = 0;
}

///
/// @brief calclutes the liner
///
/// @see for list of avialable activation fucntion see AF::ENUM_ActiFunc
/// 
/// @param a_prevNNLayerNeurons memory address to vector containing the pointer to 
///		neurons in previous layer 
/// @param a_activationFunc  activatoin function to call
/// 
void Neuron::LinerActivation(const std::vector<Neuron*>& a_prevNNLayerNeurons,
							 AF::ENUM_ActiFunc a_activationFunc)
{
	// caching data
	m_cachedActivationValue = m_activationValue;
	m_cachedActivationFuncUsed = a_activationFunc;

	// calling linear forward funciton and activation functino
	m_zValPreAct = LinerForward(a_prevNNLayerNeurons);
	m_zValPostAct = ActivationFunciton(m_zValPreAct, a_activationFunc);

}

/// 
/// @private
/// @brief calculates z value
///
/// @param a_prevNNLayerNeurons memory address to vector containing
///		 the pointer to neurons in previous layer
/// 
/// @return calculated z value 
long double Neuron::LinerForward(const std::vector<Neuron*>& a_prevNNLayerNeurons) const
{
	assert(a_prevNNLayerNeurons.size() == m_weightList.size());

	long double zVal = 0.0;

	// doing a dot product
	for(unsigned i = 0; i < m_weightList.size(); ++i)
	{
		zVal += m_weightList[ i ] * a_prevNNLayerNeurons[ i ]->m_activationValue;
	}

	zVal += m_bias;

	return zVal;
}

/// 
/// @private
/// @brief Calls the actication function accrding to the specified actication function
/// 
/// @see for list of avialable activation fucntion see AF::ENUM_ActiFunc
/// 
/// @param a_val value to pass to the activation function
/// @param a_activationFunc  activatoin function to call
/// 
/// @return calculated val
/// 
long double Neuron::ActivationFunciton(double a_val, AF::ENUM_ActiFunc a_activationFunc) const
{
	if(a_activationFunc == AF::ENUM_ActiFunc::m_sigmoid)
	{
		return AF::Sigmoid(a_val);
	}
	else if(a_activationFunc == AF::ENUM_ActiFunc::m_tanh)
	{
		return AF::Tanh(a_val);
	}
	else if(a_activationFunc == AF::ENUM_ActiFunc::m_relu)
	{
		return AF::Relu(a_val);
	}
	else if(a_activationFunc == AF::ENUM_ActiFunc::m_leakyRelu)
	{
		return AF::LeakyRelu(a_val);
	}
}
