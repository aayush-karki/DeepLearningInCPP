#pragma once

#include "ActicationFuncitons.h"

class Neuron
{
	// ===================== Public Member Function =================
public:
	Neuron(int a_numData); // default constructor
	virtual ~Neuron(); // default destructor

	// getter functions
	const std::vector<long double>* GetWeightList() const;
	const long double GetBias() const;
	const  std::vector<long double>* GetZValPreActivation() const;
	std::vector<long double>* GetActivationVector();
	
	//setter function 
	void SetActivationFunction( const AF::ENUM_ActiFunc a_ActivationFunc );

	void InitializeRandomParameters(unsigned a_previousLayerWidth); // randomizes the weight and bias 
	void LinerActivation(const std::vector<Neuron*>& a_prevNNLayerNeurons); // function for forward propagation
	const long double CalculateLoss( unsigned a_idx, uint8_t a_actualLabel ) const;
	// ===================== Private Member Function =================
private:
	long double LinerForward( unsigned a_idx, const std::vector<Neuron*>& a_prevNNLayerNeurons) const;
	long double ActivationFunciton( unsigned a_idx ) const;
	long double LinerBackward(unsigned a_idx, const std::vector<Neuron*>& a_prevNNLayerNeurons ) const;

	// ===================== Protected Data Member ====================
protected:
	std::vector<long double> m_weightList; // list of weights for each neuron from previous layer
	long double m_bias;

	std::vector<long double> m_zValPreAct; // stores the value pre activation function 
	std::vector<long double> m_activationValue; // strors the value post activation function 
	
	AF::ENUM_ActiFunc m_activationFunc;
};

inline Neuron::~Neuron()
{}

/// 
/// @brief Getter Function to get weight list 
///
/// @return memory address to weightlist vector
/// 
inline const std::vector<long double>* Neuron::GetWeightList() const
{
	return &m_weightList;
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

/// 
/// @brief Getter Function to get the vector representing activation values
///
/// @return the vector representing activation values by reference
/// 
inline std::vector<long double>* Neuron::GetActivationVector()
{
	return &m_activationValue;
}

/// 
/// @brief Getter Function to get the vector representing the z-value 
///		before passing through activaition function
///
/// @return the vector representing z-value before passing through 
///		function by reference
/// 
inline const  std::vector<long double>* Neuron::GetZValPreActivation() const
{
	return &m_zValPreAct;
}

/// 
/// @brief Setter Function to set the activation function
///
inline void Neuron::SetActivationFunction( const AF::ENUM_ActiFunc a_ActivationFunc )
{
	m_activationFunc = a_ActivationFunc;
}

///
/// @brief  calcultes the loss of the output for a image at 
///		given index 
/// 
/// @warning call only on output neuron
/// 
/// @param a_actualLabel  actual label 
/// 
/// @return loss of the neuron
/// 
inline const long double Neuron::CalculateLoss( unsigned a_idx, uint8_t a_actualLabel ) const
{
	return ( a_actualLabel * std::log( m_activationValue.at( a_idx ) ) ) + ( ( 1 - a_actualLabel ) * std::log( 1 - m_activationValue.at( a_idx ) ) );
}