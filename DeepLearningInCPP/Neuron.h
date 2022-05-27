#pragma once

#include "ActicationFuncitons.h"

class Neuron
{
	// ===================== Public Member Function =================
public:
	Neuron(int a_numData); // default constructor
	virtual ~Neuron(); // default destructor

	// getter functions
	const std::vector<long double>& GetWeightList() const;
	const long double GetBias() const;
	
	const  std::vector<long double>& GetZValPreActivation() const;
	const  std::vector<long double>& GetActivationValue() const;
	
	//setter function 
	void SetActivationValue( long double a_value ); // only for input neuron
	void SetActivationFunction( const AF::ENUM_ActiFunc a_ActivationFunc );

	virtual void InitializeRandomParameters(unsigned a_previousLayerWidth); // randomizes the weight and bias 
	virtual void LinerActivation(const std::vector<Neuron*>& a_prevNNLayerNeurons); // function for forward propagation
	const long double CalculateLoss( uint8_t a_actualLabel ) const;

	long double LinerForward(const std::vector<Neuron*>& a_prevNNLayerNeurons) const; // activation function
	long double ActivationFunciton() const;

	std::vector<long double> m_weightList; // list of weights for each neuron from previous layer
	long double m_bias;

	std::vector<long double> m_zValPreAct; // strors the value pre activation function 
	std::vector<long double> m_activationValue; // strors the value post activation function 
	
	AF::ENUM_ActiFunc m_activationFunc;
};

///
/// @public
/// @brief constructor
///
/// It initializes the data member to UNINIALIZED 
///		and cachedActivationFunc to none
/// 
/// @param a_numData number of train/test data
/// 
inline Neuron::Neuron( int a_numData ) :
	m_weightList({}), m_bias(UNINIALIZED),
	m_activationFunc(AF::ENUM_ActiFunc::m_none)
{
	m_activationValue.reserve( a_numData );
	m_zValPreAct.reserve( a_numData );
}

inline Neuron::~Neuron()
{}

/// 
/// @brief Getter Function to get weight list 
///
/// @return memory address to weightlist vector
/// 
inline const std::vector<long double>& Neuron::GetWeightList() const
{
	return m_weightList;
}

/// 
/// @brief Getter Function to get bias
///
/// @return weight of the neuron
/// 
inline const long double Neuron::GetBias() const
{
	return m_bias;
}

inline const  std::vector<long double>& Neuron::GetActivationValue() const
{
	return m_activationValue;
}

inline const  std::vector<long double>& Neuron::GetZValPreActivation() const
{
	return m_zValPreAct;
}

inline void Neuron::SetActivationValue( long double  a_value)
{
	m_activationValue = a_value;
}

inline void Neuron::SetActivationFunction( const AF::ENUM_ActiFunc a_ActivationFunc )
{
	m_activationFunc = a_ActivationFunc;
}

///
/// @brief  calcultes the loss of the output 
/// @warning call only on output neuron
/// 
/// @param a_actualLabel  actual label 
/// @return loss of the neuron
inline const long double Neuron::CalculateLoss( uint8_t a_actualLabel ) const
{
	return ( a_actualLabel * std::log( m_activationValue ) ) + ( ( 1 - a_actualLabel ) * std::log( 1 - m_activationValue ) );
}