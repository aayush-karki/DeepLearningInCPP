#include "stdafx.h"
#include "Neuron.h"
#include "RandomNumGenerator.h"


///
/// @public
/// @brief constructor
///
/// It initializes the data member to UNINIALIZED 
///		and cachedActivationFunc to none
/// 
/// @param a_numData number of train/test data
/// 
Neuron::Neuron( int a_numData ) :
	m_weightList( {} ), m_bias( UNINIALIZED ),
	m_activationFunc( AF::ENUM_ActiFunc::m_none )
{
	// resizing the vectors
	m_activationValue.resize( a_numData, UNINIALIZED );
	m_zValPreAct.resize( a_numData, UNINIALIZED );
}

/// 
/// @public
/// @brief Initializes the parameters weight to random 
///		double while normalizing it
///
void Neuron::InitializeRandomParameters( unsigned a_previousLayerWidth )
{
	for( unsigned i = 0; i < a_previousLayerWidth; ++i )
	{
		m_weightList.push_back( 10 ); ///@todo delete me
		//m_weightList.push_back( RandomNumGenerator::GetRandomNumber() );
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
	// for the number of data we have 
	for( unsigned idx = 0; idx < m_zValPreAct.size(); ++idx )
	{
		m_zValPreAct.at( idx ) =  LinerForward( idx,a_prevNNLayerNeurons );
		m_activationValue.at( idx ) =  ActivationFunciton(idx);	
	}
}

/// 
/// @private
/// @brief calculates z value
///
/// @param a_prevNNLayerNeurons memory address to vector containing
///		 the pointer to neurons in previous layer
/// @param a_idx the index of the train/test data we are doing 
///		the liner forward for
/// 
/// @return calculated z value d
/// 
long double Neuron::LinerForward( unsigned a_idx, const std::vector<Neuron*>& a_prevNNLayerNeurons ) const
{
	assert( a_prevNNLayerNeurons.size() == m_weightList.size() );

	long double zVal = 0.0;

	// doing a dot product
	for( unsigned i = 0; i < m_weightList.size(); ++i )
	{
		zVal += m_weightList[ i ] * a_prevNNLayerNeurons[ i ]->m_activationValue.at(a_idx);
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
/// @param a_idx the index of the train/test data we are doing 
///		the liner forward for
/// 
/// @return calculated val
/// 
long double Neuron::ActivationFunciton( unsigned a_idx ) const
{
	switch( m_activationFunc )
	{
		case (AF::ENUM_ActiFunc::m_sigmoid ):
		{
			return AF::Sigmoid( m_zValPreAct.at( a_idx ) );
		}
		case( AF::ENUM_ActiFunc::m_tanh ):
		{
			return AF::Tanh( m_zValPreAct.at( a_idx ) );
		}
		case( AF::ENUM_ActiFunc::m_relu ):
		{
			return AF::Relu( m_zValPreAct.at( a_idx ) );
		}
		case( AF::ENUM_ActiFunc::m_leakyRelu ):
		{
			return AF::LeakyRelu( m_zValPreAct.at( a_idx ) );
		}
		default:
		{
			return UNINIALIZED;
		}
	}
}

long double Neuron::LinerBackward( unsigned a_idx, const std::vector<Neuron*>& a_prevNNLayerNeurons ) const
{
	return 0;
}
