#pragma once

namespace AF
{
	enum class ENUM_ActiFunc
	{
		m_none,
		m_sigmoid,
		m_tanh,
		m_relu,
		m_leakyRelu
	};
	const long double LeakyReluDelta = 0.01;

	long double Sigmoid(long double a_val);
	long double SigmoidPrime(long double a_val);

	long double Tanh(long double a_val);
	long double TanhPrime(long double a_val);
	
	long double Relu(long double a_val);
	long double ReluPrime(long double a_val);

	long double LeakyRelu(long double a_val);
	long double LeakyReluPrime(long double a_val);
}
