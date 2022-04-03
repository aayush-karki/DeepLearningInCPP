#pragma once
#include <random>
#include <chrono>

class RandomNumGenerator
{
public:
	static const double m_mean; // mean
	static const double m_stddev; // standard deviation

	static void InializeSeed();
	static long double GetRandomNumber();
private:
};

