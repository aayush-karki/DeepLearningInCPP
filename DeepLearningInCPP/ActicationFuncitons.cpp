#include "stdafx.h"
#include "ActicationFuncitons.h"

long double AF::Sigmoid(long double a_val)
{
    return 1 / ( 1 + std::exp(-a_val) );
}

long double AF::SigmoidPrime(long double a_val)
{
    long double sigmond = AF::Sigmoid(a_val);
    return sigmond / ( 1 - sigmond );
}

long double AF::Tanh(long double a_val)
{
    long double posExp = std::exp(a_val);
    long double negExp = std::exp(-a_val);

    return ( posExp - negExp ) / ( posExp + negExp );
}

long double AF::TanhPrime(long double a_val)
{
    return 1 - std::pow(AF::Tanh(a_val), 2);
}

long double AF::Relu(long double a_val)
{
    if(a_val > 0)
    {
        return a_val;
    }
    else
    {
        return 0;
    }
}

long double AF::ReluPrime(long double a_val)
{
    if(a_val >= 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

long double AF::LeakyRelu(long double a_val)
{
    if(a_val > 0)
    {
        return a_val;
    }
    else
    {
        return AF::LeakyReluDelta * a_val;
    }
}

long double AF::LeakyReluPrime(long double a_val)
{
    if(a_val > 0)
    {
        return 1;
    }
    else
    {
        return AF::LeakyReluDelta;
    }
}
