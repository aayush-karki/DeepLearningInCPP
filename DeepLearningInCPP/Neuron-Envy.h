#pragma once

#include "ActicationFuncitons.h"

class Neuron
{
	// ===================== Public Member Function =====================
public:
	Neuron(); // default constructor
	
	// getter functions
	const std::vector<long double>& GetWeightList() const; 
	const long double GetBias() const;
	const long double GetActivationValue() const;
	const long double GetCachedActivationValue() const;
	const long double GetZValPreActivation() const;
	const long double GetZValPostActivation() const;
	
	//setter function 
	void SetActivationValue( long double a_value);

	virtual void InitializeRandomParameters(unsigned a_previousLayerWidth); // randomizes the weight and bias 
	virtual void LinerActivation(const std::vector<Neuron*>& a_prevNNLayerNeurons,
						 AF::ENUM_ActiFunc a_activationFunc); // function for forward propagation
	
	// ===================== Private Member Function =================
private:
	long double LinerForward(const std::vector<Neuron*>& a_prevNNLayerNeurons) const; // activation function
	long double ActivationFunciton(double a_val, AF::ENUM_ActiFunc a_activationFunc) const;

	// ===================== Protected Data Member ====================
protected:
	std::vector<long double> m_weightList; // list of weights for each neuron from previous layer
	long double m_bias;

	long double m_zValPreAct; // strors the value pre activation function 
	long double m_activationValue; // strors the value post activation function 

	long double m_cachedzValPreAct; // caches the activation value before 
	long double m_cachedActivationValue;
	

	AF::ENUM_ActiFunc m_cachedActivationFuncUsed; 


};

///
/// @public
/// @brief constructor
///
/// It initializes the data member to UNINIALIZED 
///		and cachedActivationFunc to none
/// 
inline Neuron::Neuron() :
	m_weightList({}), m_bias(UNINIALIZED),
	m_activationValue(UNINIALIZED), m_cachedActivationValue(UNINIALIZED),
	m_zValPreAct(UNINIALIZED),
	m_cachedActivationFuncUsed(AF::ENUM_ActiFunc::m_none)
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

inline const long double Neuron::GetActivationValue() const
{
	return m_activationValue;
}

inline const long double Neuron::GetCachedActivationValue() const
{
	return m_cachedActivationValue;
}

inline const long double Neuron::GetZValPreActivation() const
{
	return m_zValPreAct;
}

inline void Neuron::SetActivationValue( long double  a_value)
{
	m_activationValue = a_value;
}