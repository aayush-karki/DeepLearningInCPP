#include "stdafx.h"
#include "RandomNumGenerator.h"

const double RandomNumGenerator::m_mean = 0.0;
const double RandomNumGenerator::m_stddev = 0.5;

static std::normal_distribution<double> m_normal(RandomNumGenerator::m_mean);
static std::mt19937 m_generator; 

void RandomNumGenerator::InializeSeed()
{
	m_generator.seed(time(0));
}

long double RandomNumGenerator::GetRandomNumber()
{
	return m_normal(m_generator);
}

