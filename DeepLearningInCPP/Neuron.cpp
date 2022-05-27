#include "stdafx.h"
#include "Neuron.h"
#include "RandomNumGenerator.h"

/// 
/// @public
/// @brief Initializes the parameters weight to random 
///		double while normalizing it
///
void Neuron::InitializeRandomParameters( unsigned a_previousLayerWidth )
{
	for( unsigned i = 0; i < a_previousLayerWidth; ++i )
	{
		m_weightList.push_back( RandomNumGenerator::GetRandomNumber() );
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
void Neuron::LinerActivation( const std::vector<Neuron*>& a_prevNNLayerNeurons )
{
	// calling linear forward funciton and activation function
	m_zValPreAct = LinerForward( a_prevNNLayerNeurons );
	m_activationValue = ActivationFunciton();

	// caching data
	m_cachedActivationValue.push_back( m_activationValue );
}



/// 
/// @private
/// @brief calculates z value
///
/// @param a_prevNNLayerNeurons memory address to vector containing
///		 the pointer to neurons in previous layer
/// 
/// @return calculated z value d
long double Neuron::LinerForward( const std::vector<Neuron*>& a_prevNNLayerNeurons ) const
{
	assert( a_prevNNLayerNeurons.size() == m_weightList.size() );

	long double zVal = 0.0;

	// doing a dot product
	for( unsigned i = 0; i < m_weightList.size(); ++i )
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
/// @return calculated val
/// 
long double Neuron::ActivationFunciton() const
{
	switch( m_activationFunc )
	{
		case (AF::ENUM_ActiFunc::m_sigmoid ):
		{
			return AF::Sigmoid( m_zValPreAct );
		}
		case( AF::ENUM_ActiFunc::m_tanh ):
		{
			return AF::Tanh( m_zValPreAct );
		}
		case( AF::ENUM_ActiFunc::m_relu ):
		{
			return AF::Relu( m_zValPreAct );
		}
		case( AF::ENUM_ActiFunc::m_leakyRelu ):
		{
			return AF::LeakyRelu( m_zValPreAct );
		}
		default:
		{
			return UNINIALIZED;
		}
	}
}
