#pragma once
#include "Neuron.h"
class InputNeuron :
    public Neuron
{
    // ===================== Public Member Function =================
public:
    InputNeuron() {}; // default constructor

    // ===================== Private Member Function =================
private:
    void InitializeRandomParameters(unsigned a_previousLayerWidth) override {}; // does not reassigne the m_weight and m_bias
    void LinerActivation(const std::vector<Neuron*>& a_prevNNLayerNeurons,
                         AF::ENUM_ActiFunc a_activationFunc) override {}; // forward propagation does not apply to input neuron
};

